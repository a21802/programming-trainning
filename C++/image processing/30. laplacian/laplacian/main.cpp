#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
Mat edge;
int Thresh = 255;
const int MAX_THRSH = 255;

void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{

	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	filter2D(_src, _dst, CV_32FC1, kernelFlip, anchor, 0.0, borderType);
}

void laplacian(InputArray src, OutputArray dst, int ddepth, int borderType = BORDER_DEFAULT)
{
	//Mat lapKernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	Mat lapKernel = (Mat_<float>(3, 3) << 0, -2, 0, -2, 8, -2, 0, -2, 0);
	conv2D(src, lapKernel, dst, ddepth, Point(-1, -1), borderType);
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

	Mat dst;
	Laplacian(image, dst, CV_32F, 3);
	convertScaleAbs(dst, dst, 1.0, 0);

	//dst = 255 - dst;
	imshow("dst", dst);

	GaussianBlur(image, image, Size(5, 5), 5, 5);
	imshow("gauss", image);

	Mat img_lap;
	//image.convertTo(image, CV_32FC1, 1.0 / 255, 0);
	laplacian(image, img_lap, CV_32FC1);
	//imshow("lap", img_lap);
	convertScaleAbs(img_lap, edge, 10.0, 0);
	
	imshow("edge", edge);
	//imwrite("img3_lap.jpg", edge);

	namedWindow("edge", cv::WINDOW_AUTOSIZE);
	//createTrackbar("threshold", "edge", &Thresh, MAX_THRSH, callback_thresh);
	//callback_thresh(0, 0);

	waitKey(0);
	return 0;
}