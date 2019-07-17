#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
#include<iostream>
using namespace std;
using namespace cv;

Mat image;
Mat image_0_1;
Mat contrastImage;

int height;
int width;
int value = 150;
float segValue = 150.0;
const int MAX_VALUE = 200;
string contrastWindow = "contrast";

void callback_value(int, void*)
{

	float gamma = float(value) / segValue;

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			float pixel = powf(image_0_1.at<float>(r, c), gamma);
			contrastImage.at<float>(r, c) = pixel;
		}
	}

	cv::imshow(contrastWindow, contrastImage);

	Mat tmp;
	contrastImage.convertTo(tmp, CV_8UC1, 255, 0);
	imwrite("contrastImage.jpg", tmp);
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img3.jpg";
	image = cv::imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
	{
		cout << "no image" << endl;
		return -1;
	}

	image.convertTo(image_0_1, CV_32FC1, 1.0 / 255.0, 0);

	cv::imshow("org", image_0_1);

	height = image.rows;
	width = image.cols;
	contrastImage = Mat::zeros(image.size(), CV_32FC1);

	cv::namedWindow(contrastWindow, WINDOW_AUTOSIZE);
	cv::createTrackbar("value", contrastWindow, &value, MAX_VALUE, callback_value);
	callback_value(0, 0);

	cv::waitKey(0);
	return 0;
}