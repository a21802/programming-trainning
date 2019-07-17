#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat polar(Mat I, Point2f center, Size size, float minr = 0, float mintheta = 0, float thetaStep = 1.0 / 4, float rStep = 1.0)
{
	// 先造一個 size.height*1 大小的ri
	// 再向x方向repeat size.width次
	// 形成 size.height*size.width 大小的r
	Mat ri = Mat::zeros(Size(1, size.height), CV_32FC1);
	for (int i = 0; i < size.height; i++)
	{
		ri.at<float>(i, 0) = minr + i * rStep;
	}
	Mat r = repeat(ri, 1, size.width);

	// 先造一個 1*size.width 大小的thetaj
	// 再向y方向repeat size.height次
	// 形成 size.height*size.width 大小的theta
	Mat thetaj = Mat::zeros(Size(size.width, 1), CV_32FC1);
	for (int j = 0; j < size.width; j++)
	{
		thetaj.at<float>(0, j) = mintheta + j * thetaStep;
	}
	Mat theta = repeat(thetaj, size.height, 1);

	Mat x, y;
	polarToCart(r, theta, x, y, true);

	// 座標原點移到中心
	x += center.x;
	y += center.y;
	// 造一個size大小的灰階矩陣
	// 用途為下面做插值時若超出範圍, 至少還有個灰階色
	Mat dst = 125 * Mat::ones(size, CV_8UC1);
	for (int i = 0; i < size.height; i++)
	{
		for (int j = 0; j < size.width; j++)
		{
			float xij = x.at<float>(i, j);
			float yij = y.at<float>(i, j);
			int nearestx = int(round(xij));
			int nearesty = int(round(yij));
			if ((0 <= nearestx && nearestx < I.cols) &&
				(0 <= nearesty && nearesty < I.rows))
				dst.at<uchar>(i, j) = I.at<uchar>(nearesty, nearestx);
		}
	}
	return dst;
}

int main(int argc, char* argv[])
{

	string str = "..//..//img//disk.jpg";

	Mat I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return -1;

	float thetaStep = 1.0 / 4; // theta步長
	float minr = 270;          // r的範圍(270, 340)實驗獲得, 故下行輸出圖片的高為70
	Size size(int(360 / thetaStep), 70); // 輸出圖片的大小 70*1440 
	Mat dst = polar(I, Point2f(508, 503), size, minr); // (508, 503)為圖型中心點座標
	Mat dst2;
	resize(I, dst2, Size(), 0.5, 0.5);

	flip(dst, dst, 0);

	imshow("I", dst2);
	imshow("極座標轉換", dst);
	imwrite("result.jpg", dst);
	waitKey(0);
	return 0;
}
