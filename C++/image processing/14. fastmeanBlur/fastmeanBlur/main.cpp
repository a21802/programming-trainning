#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat fastMeanBlur(Mat img, Size winSize, int borderType, Scalar value = Scalar())
{
	int hei = winSize.height;
	int wid = winSize.width;
	CV_Assert(hei % 2 == 1 && wid % 2 == 1);

	int hh = (hei - 1) / 2;
	int ww = (wid - 1) / 2;

	float area = float(hei * wid);

	Mat paddImg;
	cv::copyMakeBorder(img, paddImg, hh, hh, ww, ww, borderType, value);
	// 圖像積分(累加)
	Mat inte;
	cv::integral(paddImg, inte, CV_32FC1);

	int rows = img.rows;
	int cols = img.cols;
	int r = 0, c = 0;
	Mat meanImg = Mat::zeros(img.size(), CV_32FC1);
	for (int h = hh; h < hh + rows; h++)
	{
		for (int w = ww; w < ww + cols; w++)
		{
			// 因為integral會在上與左補0, 所以index會向右與向下多1
			float bottomRight = inte.at<float>(h + hh + 1, w + ww + 1);
			float topLeft = inte.at<float>(h - hh, w - ww);
			float topRight = inte.at<float>(h + hh + 1, w - ww);
			float bottomLeft = inte.at<float>(h - hh, w + ww + 1);
			meanImg.at<float>(r, c) = (bottomRight + topLeft - topRight - bottomLeft) / area;
			c++;
		}
		r++;
		c = 0;
	}
	return meanImg;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img5.jpg";
	Mat img = imread(str, IMREAD_GRAYSCALE);
	if (!img.data)
		return -1;

	Mat meanImg = fastMeanBlur(img, Size(5, 5), BORDER_REFLECT101);

	meanImg.convertTo(meanImg, CV_8UC1, 1.0, 0);

	imshow("org", img);
	imshow("mean blur", meanImg);
	waitKey(0);
	return 0;
}