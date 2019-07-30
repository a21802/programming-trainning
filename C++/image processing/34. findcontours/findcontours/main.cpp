#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
	string str = "..//..//img//img12.jpg";
	Mat img = imread(str, IMREAD_GRAYSCALE);
	if (!img.data)
		return -1;

	GaussianBlur(img, img, Size(3, 3), 0.5);
	Mat binaryImg;
	Canny(img, binaryImg, 50, 200);
	imshow("edge", binaryImg);
	//imwrite("cannyEdge.jpg", binaryImg);

	vector<vector<Point>> contours;
	vector<Vec4i> hei;
	findContours(binaryImg, contours, hei, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));


	int num = contours.size();
	for (int i = 0; i < num; i++)
	{

		Rect rect = boundingRect(Mat(contours[i]));
		if (rect.area() > 1500)
		{

			rectangle(img, rect, Scalar(255), 2);
			cout << rect.area() << endl;
		}
	}
	imshow("img", img);
	//imwrite("img0.jpg", img);
	waitKey(0);
	return 0;
}