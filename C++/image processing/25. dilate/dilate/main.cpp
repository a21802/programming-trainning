#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
int r = 0;
int MAX_R = 20;
Mat I;
Mat D;

void callBack(int, void*)
{

	Mat s = getStructuringElement(MORPH_RECT, Size(2 * r + 1, 2 * r + 1));
	dilate(I, D, s);
	imshow("dilate", D);
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img9.jpg";
	I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return -1;

	imshow("I", I);

	namedWindow("dilate", WINDOW_AUTOSIZE);

	createTrackbar("radius", "dilate", &r, MAX_R, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}