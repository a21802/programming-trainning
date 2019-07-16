#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char const* argv[]) {
	/* �e�� */
	Mat img(270, 720, CV_8UC3, Scalar(56, 50, 38));
	/* ���u */
	line(img, Point(20, 40), Point(120, 140), Scalar(255, 0, 0), 3);
	/* ��ߤ�� */
	rectangle(img, Point(150, 40), Point(250, 140), Scalar(0, 0, 255), -1);
	/* ��߶� */
	circle(img, Point(330, 90), 50, Scalar(0, 255, 0), -1);
	/* �Ť߾�� */
	ellipse(img, Point(460, 90), Size(60, 40), 45, 0, 360, Scalar(255, 255, 0), 2);
	/* ���W�h�ϧ� */
	Point points[1][5];
	int x = 40, y = 540;
	points[0][0] = Point(0 + y, 50 + x);
	points[0][1] = Point(40 + y, 0 + x);
	points[0][2] = Point(110 + y, 35 + x);
	points[0][3] = Point(74 + y, 76 + x);
	points[0][4] = Point(28 + y, 96 + x);
	const Point* ppt[1] = { points[0] };
	int npt[] = { 5 };
	polylines(img, ppt, npt, 1, 1, Scalar(0, 255, 255), 3);
	/* ø�X��r */
	putText(img, "Test Passed !!", Point(10, 230), 0, 3, Scalar(255, 170, 130), 3);
	/* �}�ҵe�� */
	namedWindow("OpenCV Test By:Charlotte.HonG", WINDOW_AUTOSIZE);
	imshow("OpenCV Test By:Charlotte.HonG", img);
	waitKey(0);
	return 0;
}