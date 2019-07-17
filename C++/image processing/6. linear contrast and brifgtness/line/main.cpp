#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
#include<iostream>
using namespace cv;
using namespace std;

Mat image;
Mat contrastImage;

int g_iContrastValue = 20;
float g_fContrastValueOrg = float(g_iContrastValue);
int g_iBrightValue = 0;
string contrastWindow = "ContrastAndBright";

void ContrastAndBright(int, void*)
{

	float a = float(g_iContrastValue) / g_fContrastValueOrg;

	for (int r = 0; r < image.rows; r++)
	{
		for (int c = 0; c < image.cols; c++)
		{
			float pixel = a * image.at<uchar>(r, c) + g_iBrightValue; // 線性調整對比
			pixel = round(pixel);

			if (pixel > 255)
				pixel = 255;
			contrastImage.at<uchar>(r, c) = uchar(pixel);
		}
	}
	
	imshow(contrastWindow, contrastImage);
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img1.jpg";
	image = cv::imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
	{
		std::cout << "no img" << std::endl;
		return -1;
	}
	
	//cv::imshow("org", image);
	
	contrastImage = cv::Mat::zeros(image.size(), CV_8UC1);
	namedWindow(contrastWindow, WINDOW_AUTOSIZE);
	// 創建滑桿
	createTrackbar("contrast", contrastWindow, &g_iContrastValue, 120, ContrastAndBright);
	createTrackbar("brightness", contrastWindow, &g_iBrightValue, 150, ContrastAndBright);
	ContrastAndBright(0, 0);

	waitKey(0);
	return 0;
}