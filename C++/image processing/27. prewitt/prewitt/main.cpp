#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

Mat edge;
int Thresh = 128;
const int MAX_THRSH = 255;

void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{

	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	filter2D(_src, _dst, CV_32FC1, kernelFlip, anchor, 0.0, borderType);
}

//void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
//{
//	Mat src_kerX;
//	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);
//	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
//}

void sepConv2D(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}

void prewitt(InputArray src, OutputArray dst, int ddepth, int x, int y = 0, int borderType = BORDER_DEFAULT)
{
	CV_Assert(!(x == 0 && y == 0));

	if (x != 0)
	{
		Mat prewitt_x_y = (Mat_<float>(3, 1) << 1, 1, 1);
		Mat prewitt_x_x = (Mat_<float>(1, 3) << 1, 0, -1);
		sepConv2D(src, dst, ddepth, prewitt_x_y, prewitt_x_x, Point(-1, -1), borderType);
	}
	if (y != 0)
	{
		Mat prewitt_y_x = (Mat_<float>(1, 3) << 1, 1, 1);
		Mat prewitt_y_y = (Mat_<float>(3, 1) << 1, 0, -1);
		sepConv2D(src, dst, ddepth, prewitt_y_x, prewitt_y_y, Point(-1, -1), borderType);
	}
}
void callback_thresh(int, void*)
{
	Mat copyEdge = edge.clone();
	Mat thresh_edge;
	threshold(copyEdge, thresh_edge, Thresh, MAX_THRSH, cv::THRESH_BINARY);
	imshow("edge", thresh_edge);
}

int main(int argc, char* argv[])
{
	string str = "..//..//img//house1.jpg";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
	{
		cout << "no image" << endl;
		return -1;
	}
	imshow("org", image);

	Mat img_prewitt_x;
	prewitt(image, img_prewitt_x, CV_32FC1, 1, 0);

	Mat img_prewitt_y;
	prewitt(image, img_prewitt_y, CV_32FC1, 0, 1);

	Mat abs_img_prewitt_x, abs_img_prewitt_y;
	convertScaleAbs(img_prewitt_x, abs_img_prewitt_x, 1, 0);
	convertScaleAbs(img_prewitt_y, abs_img_prewitt_y, 1, 0);
	imshow("v edge", abs_img_prewitt_x);
	imshow("h edge", abs_img_prewitt_y);

	Mat img_prewitt_x2, image_prewitt_y2;
	pow(img_prewitt_x, 2.0, img_prewitt_x2);
	pow(img_prewitt_y, 2.0, image_prewitt_y2);
	sqrt(img_prewitt_x2 + image_prewitt_y2, edge);

	edge.convertTo(edge, CV_8UC1);
	//imshow("edge", edge);

	Mat tempedge;
	threshold(edge, tempedge, 25, MAX_THRSH, cv::THRESH_BINARY);
	//imwrite("img3_thresh_edge_25.jpg", tempedge);

	namedWindow("edge", cv::WINDOW_AUTOSIZE);
	createTrackbar("threshold", "edge", &Thresh, MAX_THRSH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}