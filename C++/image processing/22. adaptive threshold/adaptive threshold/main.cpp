#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat adaptiveThreshold_S(const Mat& image, Size blockSize, float ratio)
{

	int rows = image.rows;
	int cols = image.cols;

	Mat threshImage = Mat::zeros(image.size(), CV_8UC1);
	//
	int h = (blockSize.height - 1) / 2;
	int w = (blockSize.width - 1) / 2;

	Mat imageIntegral;
	integral(image, imageIntegral, CV_32FC1);
	imageIntegral = imageIntegral(Rect(1, 1, cols, rows)).clone();

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int tl_r = r - h > 0 ? r - h : 0;
			int tl_c = c - w > 0 ? c - w : 0;
			int br_r = r + h < rows ? r + h : rows - 1;
			int br_c = c + w < cols ? c + w : cols - 1;

			float regionSum = imageIntegral.at<float>(br_r, br_c) +
				imageIntegral.at<float>(tl_r, tl_c) -
				imageIntegral.at<float>(tl_r, br_c) -
				imageIntegral.at<float>(br_r, tl_c);
			int count = (br_r - tl_r + 1) * (br_c - tl_c + 1);
			int pixel = int(image.at<uchar>(r, c));
			if (pixel * count < (1 - ratio) * regionSum)
				threshImage.at<uchar>(r, c) = 0;
			else
				threshImage.at<uchar>(r, c) = 255;
		}
	}
	return threshImage;
}

enum METHOD { MEAN, GAUSS, MEDIAN };
Mat adaptiveThresh(Mat I, int radius, float ratio, METHOD method = MEAN)
{

	Mat I_smooth;
	switch (method)
	{
	case MEAN:
		boxFilter(I, I_smooth, CV_32FC1, Size(2 * radius + 1, 2 * radius + 1));//均值平滑
		break;
	case GAUSS:
		GaussianBlur(I, I_smooth, Size(2 * radius + 1, 2 * radius + 1), 0, 0);//高斯平滑
		I_smooth.convertTo(I_smooth, CV_32FC1);
		break;
	case MEDIAN:
		medianBlur(I, I_smooth, 2 * radius + 1);//中值平滑
		I_smooth.convertTo(I_smooth, CV_32FC1);
		break;
	default:
		break;
	}

	I.convertTo(I, CV_32FC1);
	Mat diff = I - (1.0 - ratio) * I_smooth;

	Mat out = Mat::zeros(diff.size(), CV_8UC1);
	for (int r = 0; r < out.rows; r++)
	{
		for (int c = 0; c < out.cols; c++)
		{
			if (diff.at<float>(r, c) >= 0)
				out.at<uchar>(r, c) = 255;
		}
	}
	return out;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//blocks.png";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
	{
		cout << "no image" << endl;
		return -1;
	}

	Mat threshImage = adaptiveThresh(image, 21, 0.15, MEDIAN);
	imshow("org", image);
	imshow("image", threshImage);
	//imwrite("adThmean43.jpg", threshImage);
	waitKey(0);
	return 0;
}
