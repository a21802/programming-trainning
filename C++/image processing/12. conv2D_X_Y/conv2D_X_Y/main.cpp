#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include <iomanip>
using namespace cv;
using namespace std;

void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}


void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}

void showMat(Mat& src)
{
	for (int r = 0; r < src.rows; r++)
	{
		for (int c = 0; c < src.cols; c++)
		{
			cout << setw(4) << src.at<float>(r, c) << ",";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	Mat src = (Mat_<float>(5, 5) << 1, 2, 3, 10, 12,
									32, 43, 12, 4, 190,
									12, 234, 78, 0, 12,
									43, 90, 32, 8, 90,
									71, 12, 4, 98, 123);

	Mat kernel = (Mat_<float>(3, 3) << 1, 0, -1, 
									   1, 0, -1, 
									   1, 0, -1);
	Mat kernel1 = (Mat_<float>(1, 3) << 1, 0, -1);
	Mat kernel2 = (Mat_<float>(3, 1) << 1, 1, 1);

	Mat result, c_same1, c_same2;;

	conv2D(src, kernel, result, CV_32FC1, Point(-1, -1), BORDER_REFLECT);
	sepConv2D_X_Y(src, c_same1, CV_32FC1, kernel1, kernel2, Point(-1, -1), 2);
	sepConv2D_X_Y(src, c_same2, CV_32FC1, kernel2, kernel1, Point(-1, -1), 2);

	showMat(result);

	for (int i = 0; i < 25; i++) cout << "=";
	cout << endl;

	showMat(c_same1);

	for (int i = 0; i < 25; i++) cout << "=";
	cout << endl;

	showMat(c_same2);

	system("pause");
	return 0;
}