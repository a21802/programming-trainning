#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat polar(Mat I, Point2f center, Size size, float minr = 0, float mintheta = 0, float thetaStep = 1.0 / 4, float rStep = 1.0)
{
	// ���y�@�� size.height*1 �j�p��ri
	// �A�Vx��Vrepeat size.width��
	// �Φ� size.height*size.width �j�p��r
	Mat ri = Mat::zeros(Size(1, size.height), CV_32FC1);
	for (int i = 0; i < size.height; i++)
	{
		ri.at<float>(i, 0) = minr + i * rStep;
	}
	Mat r = repeat(ri, 1, size.width);

	// ���y�@�� 1*size.width �j�p��thetaj
	// �A�Vy��Vrepeat size.height��
	// �Φ� size.height*size.width �j�p��theta
	Mat thetaj = Mat::zeros(Size(size.width, 1), CV_32FC1);
	for (int j = 0; j < size.width; j++)
	{
		thetaj.at<float>(0, j) = mintheta + j * thetaStep;
	}
	Mat theta = repeat(thetaj, size.height, 1);

	Mat x, y;
	polarToCart(r, theta, x, y, true);

	// �y�Э��I���줤��
	x += center.x;
	y += center.y;
	// �y�@��size�j�p���Ƕ��x�}
	// �γ~���U�������ȮɭY�W�X�d��, �ܤ��٦��ӦǶ���
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

	float thetaStep = 1.0 / 4; // theta�B��
	float minr = 270;          // r���d��(270, 340)������o, �G�U���X�Ϥ�������70
	Size size(int(360 / thetaStep), 70); // ��X�Ϥ����j�p 70*1440 
	Mat dst = polar(I, Point2f(508, 503), size, minr); // (508, 503)���ϫ������I�y��
	Mat dst2;
	resize(I, dst2, Size(), 0.5, 0.5);

	flip(dst, dst, 0);

	imshow("I", dst2);
	imshow("���y���ഫ", dst);
	imwrite("result.jpg", dst);
	waitKey(0);
	return 0;
}
