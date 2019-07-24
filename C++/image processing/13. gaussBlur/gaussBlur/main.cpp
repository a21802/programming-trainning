#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat createGaussKernel(float sigma, int H, int W)
{
	CV_Assert(H % 2 == 1 && W % 2 == 1);
	if (sigma <= 0)
		sigma = sqrt(float(W + H));

	Mat gaussMatrix(Size(W, H), CV_32FC1);
	int cH = (H - 1) / 2;
	int cW = (W - 1) / 2;
	float coefficient = 1.0 / (sqrt(2 * CV_PI) * sigma);
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			float norm2 = pow(r - cH, 2.0) + pow(c - cW, 2.0);
			gaussMatrix.at<float>(r, c) = coefficient * exp(-norm2 / (2 * pow(sigma, 2)));
		}
	}

	float sumGM = sum(gaussMatrix)[0];

	Mat gaussKernel = gaussMatrix / sumGM;
	return gaussKernel;
}

void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}


void sepConv2D_Y_X(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}

Mat  gaussBlur(const Mat& image, Size winSize, float sigma, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{

	CV_Assert(winSize.width % 2 == 1 && winSize.height % 2 == 1);

	Mat gKernel_y = getGaussianKernel(sigma, winSize.height, CV_64F);
	Mat gKernel_x = getGaussianKernel(sigma, winSize.width, CV_64F);
	gKernel_x = gKernel_x.t(); // Âà¸m
	Mat blurImage;
	sepConv2D_Y_X(image, blurImage, CV_32FC1, gKernel_y, gKernel_x, Point(-1, -1));
	return blurImage;
}

int main(int argc, char* argv[])
{
	string str = "..//..//img//img2.jpg";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
	{
		cout << "no image" << endl;
		return 0;
	}
	imshow("org", image);

	Mat blurImage = gaussBlur(image, Size(21, 21), 3);

	for (int r = 0; r < image.rows; r++)
	{
		for (int c = 0; c < image.cols; c++)
		{
			float pixel = blurImage.at<float>(r, c);
			blurImage.at<float>(r, c) = roundf(pixel);
		}
	}
	blurImage.convertTo(blurImage, CV_8UC1);
	imshow("gauss8bit", blurImage);

	Mat image_0_1;
	double maxVal;
	minMaxLoc(image, NULL, &maxVal, NULL, NULL, Mat());
	image.convertTo(image_0_1, CV_32FC1, 1.0 / maxVal);
	Mat blurImage_0_1 = gaussBlur(image_0_1, Size(21, 21), 3);
	imshow("gauss0_1", blurImage_0_1);
	waitKey(0);
	return 0;
}