#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat I;
Mat d;
Mat element;
string window = "morph";

int r = 1;
int MAX_R = 20;

int i = 1;
int MAX_I = 20;
void callBack(int, void*)
{
	element = getStructuringElement(MORPH_RECT, Size(2 * r + 1, 2 * r + 1));
	morphologyEx(I, d, MORPH_BLACKHAT, element, Point(-1, -1), i);
	imshow(window, d);
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//dise.jpg";
	I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return 0;

	imshow("org", I);

	namedWindow(window, 1);

	createTrackbar("radius", window, &r, MAX_R, callBack);
	createTrackbar("times", window, &i, MAX_I, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}