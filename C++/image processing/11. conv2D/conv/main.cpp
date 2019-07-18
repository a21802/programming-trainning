#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{

	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);

	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
int main(int argc, char* argv[])
{
	Mat src = (Mat_<float>(2, 2) << 1, 2, 3, 4);

	Mat kernel = (Mat_<int>(2, 2) << -1, -2, 2, 1);
	Mat result;

	conv2D(src, kernel, result, CV_32FC1, Point(0, 0), BORDER_CONSTANT);

	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			cout << result.at<float>(r, c) << ",";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}