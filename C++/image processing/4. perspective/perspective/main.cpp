#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
Mat I;
Mat pI;
Point2f IPoint, pIPoint;
int i = 0, j = 0;
Point2f src[4];
Point2f dst[4];

void mouse_I(int event, int x, int y, int flags, void* param)
{
	switch (event)
	{
	case EVENT_LBUTTONDOWN:  // ���U�ƹ�����
		
		IPoint = Point2f(x, y);
		break;
	case EVENT_LBUTTONUP:    // ��}�ƹ�����
		if (i <= 3) {
			src[i] = IPoint;
			circle(I, src[i], 7, Scalar(0), 3); // args: �b�|, �C��(�Ƕ��G��), ��t�ʲ�
			i += 1;
		}
		break;
	default:
		break;
	}
}

void mouse_pI(int event, int x, int y, int flags, void* param)
{
	switch (event)
	{
	case EVENT_LBUTTONDOWN:

		pIPoint = Point2f(x, y);
		break;
	case EVENT_LBUTTONUP:
		if (j <= 3) {
			dst[j] = pIPoint;
			circle(pI, dst[j], 7, Scalar(0), 3);
			j += 1;
		}	
		break;
	default:
		break;
	}
}
int main(int argc, char* argv[])
{
	std::string str = "..//..//img//bird.jpg";
	I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return 0;

	pI = 200 * Mat::ones(I.size(), CV_8UC1);
	// �b��ϵ����w�q�ƹ��ƥ�
	namedWindow("I", 1); 
	setMouseCallback("I", mouse_I, NULL);
	// �b��X�����w�q�ƹ��ƥ�
	namedWindow("pI", 1);
	setMouseCallback("pI", mouse_pI, NULL);
	//imshow("I", I);
	//imshow("pI", pI);
	while (!(i == 4 && j == 4))
	{
		imshow("I", I);
		imshow("pI", pI);
		if (waitKey(50) == 'q')
			break;
	}
	imshow("I", I);
	imshow("pI", pI);
	//imwrite("I.jpg", I);
	//imwrite("pI.jpg", pI);

	// �����ƹ��ƥ�
	setMouseCallback("I", NULL, NULL);
	setMouseCallback("pI", NULL, NULL);

	Mat p = getPerspectiveTransform(src, dst);

	Mat result;
	warpPerspective(I, result, p, pI.size());
	imshow("��v�Z���ĪG", result);
	//imwrite("result.jpg", result);
	waitKey(0);
	return 0;
}
