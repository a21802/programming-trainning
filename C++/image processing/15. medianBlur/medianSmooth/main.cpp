#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include <time.h>
using namespace std;
using namespace cv;

class Timer
{
public:
	void start() { this->m_start = clock(); }
	void end() { this->m_end = clock(); }
	double pstime() {return ((double)(this->m_end - this->m_start)) / CLOCKS_PER_SEC; }

private:
	clock_t m_start;
	clock_t m_end;
};

Mat medianSmooth(const Mat& I, Size size, int iswitch, int borderType = BORDER_DEFAULT)
{
	CV_Assert(I.type() == CV_8UC1);
	int H = size.height;
	int W = size.width;

	CV_Assert(H > 0 && W > 0);
	CV_Assert(H % 2 == 1 && W % 2 == 1);

	int h = (H - 1) / 2;
	int w = (W - 1) / 2;
	Mat Ip;
	copyMakeBorder(I, Ip, h, h, w, w, borderType);

	int rows = I.rows;
	int cols = I.cols;

	Mat medianI(I.size(), CV_8UC1);
	int i = 0, j = 0;

	int index = (H * W - 1) / 2;

	switch (iswitch)
	{
	case 1:
		for (int r = h; r < h + rows; r++)
		{
			for (int c = w; c < w + cols; c++)
			{

				Mat region = Ip(Rect(c - w, r - h, W, H)).clone();
				region = region.reshape(1, 1);
				vector<uchar> v = region;
				//nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
				std::sort(v.begin(), v.end());
				medianI.at<uchar>(i, j) = v[v.size() / 2];
				j++;
			}
			i++;
			j = 0;
		}
		break;
	case 2:
		for (int r = h; r < h + rows; r++)
		{
			for (int c = w; c < w + cols; c++)
			{

				Mat region = Ip(Rect(c - w, r - h, W, H)).clone();
				region = region.reshape(1, 1);
				cv::sort(region, region, SORT_EVERY_ROW);

				uchar mValue = region.at<uchar>(0, index);
				medianI.at<uchar>(i, j) = mValue; 
				j++;
			}
			i++;
			j = 0;
		}
	default:
		break;
	}
	
	return medianI;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//bird_noise.jpg";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
		return -1;

	int filter_size = 7;

	Timer t1, t2;
	t1.start();
	Mat medianImage1 = medianSmooth(image, Size(filter_size, filter_size), 1);
	t1.end();
	t2.start();
	Mat medianImage2 = medianSmooth(image, Size(filter_size, filter_size), 2);
	t2.end();

	imshow("org", image);
	imshow("median smooth 1", medianImage1);
	imshow("median smooth 2", medianImage2);
	//cout << "nth_element: " << t1.pstime() << endl;
	cout << "std::sort: " << t2.pstime() << endl;
	cout << "cv::sort: " << t2.pstime() << endl;
	waitKey(0);
	return 0;
}