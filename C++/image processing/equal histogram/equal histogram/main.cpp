#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& image)
{

	Mat histogram = Mat::zeros(Size(256, 1), CV_32SC1);
	int rows = image.rows;
	int cols = image.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int index = int(image.at<uchar>(r, c));
			histogram.at<int>(0, index) += 1;
		}
	}
	return histogram;
}

Mat equalHist(Mat image)
{
	CV_Assert(image.type() == CV_8UC1); // 不相等則跳警告

	int rows = image.rows;
	int cols = image.cols;
	// 灰階直方圖
	Mat grayHist = calcGrayHist(image);
	// 累加灰階直方圖
	Mat zeroCumuMoment = Mat::zeros(Size(256, 1), CV_32SC1);
	for (int p = 0; p < 256; p++)
	{
		if (p == 0)
			zeroCumuMoment.at<int>(0, p) = grayHist.at<int>(0, 0);
		else
			zeroCumuMoment.at<int>(0, p) = zeroCumuMoment.at<int>(0, p - 1) + grayHist.at<int>(0, p);
	}
	// 根據累加直方圖的數值與全圖大小得到一比例關係
	// 根據這比例轉換灰階值
	Mat outPut_q = Mat::zeros(Size(256, 1), CV_8UC1);
	float cofficient = 256.0 / (rows * cols);
	for (int p = 0; p < 256; p++)
	{
		float q = cofficient * zeroCumuMoment.at<int>(0, p) - 1;
		if (q >= 0)
			outPut_q.at<uchar>(0, p) = uchar(floor(q));
		else
			outPut_q.at<uchar>(0, p) = 0;
	}

	Mat euqalHistImage = Mat::zeros(image.size(), CV_8UC1);
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int p = image.at<uchar>(r, c);
			euqalHistImage.at<uchar>(r, c) = outPut_q.at<uchar>(0, p);
			// 意思為 I'(index) = table( I(index) )
		}
	}
	return euqalHistImage;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img1.jpg";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("org", image);

	Mat result = equalHist(image);
	imshow("equal histogram", result);
	waitKey(0);
	return 0;
}