#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
int main(int argc, char* argv[])
{

	Mat src1 = Mat::zeros(Size(400, 400), CV_8UC1);
	cv::rectangle(src1, Rect(75, 100, 200, 200), Scalar(255), FILLED);
	imshow("src1", src1);
	Mat src2 = Mat::zeros(Size(400, 400), CV_8UC1);
	cv::circle(src2, Point(275, 200), 100, Scalar(255), FILLED);
	imshow("src2", src2);

	Mat dst_and;
	bitwise_and(src1, src2, dst_and);
	imshow("and operation", dst_and);

	Mat dst_or;
	bitwise_or(src1, src2, dst_or);
	imshow("or operation", dst_or);

	Mat dst_not;
	bitwise_not(src1, dst_not);
	imshow("not operation", dst_not);
	waitKey(0);
	return 0;
}