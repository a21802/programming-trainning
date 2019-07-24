#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int factorial(int n)
{
	int fac = 1;
	if (n == 0)
		return fac;
	for (int i = 1; i <= n; i++)
		fac *= i;
	return fac;
}

Mat getPascalSmooth(int n)
{
	Mat pascalSmooth = Mat::zeros(Size(n, 1), CV_32FC1);
	for (int i = 0; i < n; i++)
		pascalSmooth.at<float>(0, i) = factorial(n - 1) / (factorial(i) * factorial(n - 1 - i));
	return pascalSmooth;
}

Mat getPascalDiff(int n)
{
	Mat pascalDiff = Mat::zeros(Size(n, 1), CV_32FC1);
	Mat pascalSmooth_previous = getPascalSmooth(n - 1);
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			pascalDiff.at<float>(0, i) = 1;
		else if (i == n - 1)
			pascalDiff.at<float>(0, i) = -1;
		else
			pascalDiff.at<float>(0, i) = pascalSmooth_previous.at<float>(0, i) - pascalSmooth_previous.at<float>(0, i - 1);
	}
	return pascalDiff;
}

void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}

void sepConv2D(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}

//void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
//{
//	Mat src_kerX;
//	conv2D(src, kernelX, src_kerX, CV_32F, anchor, borderType);
//	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
//}

Mat sobel(Mat image, int x_flag, int y_flag, int winSize, int borderType)
{

	CV_Assert(winSize >= 3 && winSize % 2 == 1);
	Mat pascalSmooth = getPascalSmooth(winSize);
	Mat pascalDiff = getPascalDiff(winSize);
	Mat image_con_sobel;

	if (x_flag != 0)
	{
		sepConv2D(image, image_con_sobel, CV_32FC1, pascalSmooth.t(), pascalDiff, Point(-1, -1), borderType);
	}

	if (x_flag == 0 && y_flag != 0)
	{
		sepConv2D(image, image_con_sobel, CV_32FC1, pascalSmooth, pascalDiff.t(), Point(-1, -1), borderType);
	}
	return image_con_sobel;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//house1.jpg";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("org", image);

	// abs() + convertTo() == convertScaleAbs()
	Mat image_Y_X = sobel(image, 1, 0, 3, 4);
	Mat imageYX_abs = abs(image_Y_X);
	Mat imageYX_gray;
	imageYX_abs.convertTo(imageYX_gray, CV_8UC1, 1.0, 0);
	imshow("v edge", imageYX_gray);

	Mat image_X_Y = sobel(image, 0, 1, 3, 4);
	Mat imageXY_abs = abs(image_X_Y);
	Mat imageXY_gray;
	imageXY_abs.convertTo(imageXY_gray, CV_8UC1, 1.0, 0);
	imshow("h edge", imageXY_gray);

	//Mat abs_img_prewitt_x, abs_img_prewitt_y;
	//convertScaleAbs(image_Y_X, abs_img_prewitt_x, 1, 0);
	//convertScaleAbs(image_X_Y, abs_img_prewitt_y, 1, 0);
	//imshow("av edge", abs_img_prewitt_x);
	//imshow("ah edge", abs_img_prewitt_y);

	Mat edge;
	magnitude(image_Y_X, image_X_Y, edge);

	edge.convertTo(edge, CV_8UC1, 1.0, 0);
	imshow("edge", edge);
	//imwrite("sobeledge.jpg", edge);
	waitKey(0);
	return 0;
}