#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

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

int otsu(const Mat& image, Mat& OtsuThreshImage)
{

	Mat histogram = calcGrayHist(image);

	Mat normHist;
	histogram.convertTo(normHist, CV_32FC1, 1.0 / (image.rows * image.cols), 0.0);

	Mat zeroCumuMoment = Mat::zeros(Size(256, 1), CV_32FC1);
	Mat oneCumuMoment = Mat::zeros(Size(256, 1), CV_32FC1);
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			zeroCumuMoment.at<float>(0, i) = normHist.at<float>(0, i);
			oneCumuMoment.at<float>(0, i) = i * normHist.at<float>(0, i);
		}
		else
		{
			zeroCumuMoment.at<float>(0, i) = zeroCumuMoment.at<float>(0, i - 1) + normHist.at<float>(0, i);
			oneCumuMoment.at<float>(0, i) = oneCumuMoment.at<float>(0, i - 1) + i * normHist.at<float>(0, i);
		}
	}

	Mat variance = Mat::zeros(Size(256, 1), CV_32FC1);

	float mean = oneCumuMoment.at<float>(0, 255);
	for (int i = 0; i < 255; i++)
	{
		if (zeroCumuMoment.at<float>(0, i) == 0 || zeroCumuMoment.at<float>(0, i) == 1)
			variance.at<float>(0, i) = 0;
		else
		{
			float cofficient = zeroCumuMoment.at<float>(0, i) * (1.0 - zeroCumuMoment.at<float>(0, i));
			variance.at<float>(0, i) = pow(mean * zeroCumuMoment.at<float>(0, i) - oneCumuMoment.at<float>(0, i), 2.0) / cofficient;
		}
	}

	Point maxLoc;
	minMaxLoc(variance, NULL, NULL, NULL, &maxLoc);
	int otsuThresh = maxLoc.x;

	threshold(image, OtsuThreshImage, otsuThresh, 255, THRESH_BINARY);
	return otsuThresh;
}

int main(int argc, char* argv[])
{
	string str = "..//..//img//dog.jpg";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
	{
		cout << "no image" << endl;
		return -1;
	}

	Mat otsuThreshImage;
	int thresh = 0;
	thresh = otsu(image, otsuThreshImage);
	cout << "threshold value¡G" << thresh << endl;

	imshow("Otsu", otsuThreshImage);
	//imwrite("otsu.jpg", otsuThreshImage);
	waitKey(0);
	return 0;
}