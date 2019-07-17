#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void calGrayHist(string name, const Mat& image)
{
	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };
	Mat histImg;
	calcHist(&image, 1, 0, Mat(), histImg, 1, &histSize, &histRange);

	float histMaxValue = 0;
	for (int i = 0; i < histSize; i++) {
		float tempValue = histImg.at<float>(i);
		if (histMaxValue < tempValue) {
			histMaxValue = tempValue;
		}
	}

	Mat showHistImg(256, 256, CV_8UC1, Scalar(255));
	float scale = (0.9 * 256) / histMaxValue;
	for (int i = 0; i < histSize; i++) {
		int intensity = static_cast<int>(histImg.at<float>(i) * scale);
		line(showHistImg, Point(i, 255), Point(i, 255 - intensity), Scalar(0));
	}

	imshow(name + "_histogram", showHistImg);
}

int main(int argc, char* argv[])
{
	string str = "..//..//img//img2.jpg";
	Mat src = imread(str, IMREAD_ANYCOLOR);
	if (!src.data)
		return -1;

	Mat dst;
	normalize(src, dst, 255, 0, NORM_MINMAX, CV_8U);
	imshow("org", src);
	calGrayHist("org", src);
	imshow("normalize", dst);
	calGrayHist("normalize", dst);
	waitKey(0);
	return 0;
}