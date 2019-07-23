#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;

Mat image;
int thresh = 100;
const int MAX_THRESH = 255;

void callback_thresh(int, void*)
{
	Mat threshImage;
	threshold(image, threshImage, thresh, MAX_THRESH, THRESH_BINARY);
	imshow("binarize", threshImage);
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img8.jpg";
	image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
	{
		cout << "no image" << endl;
		return -1;
	}

	namedWindow("binarize", WINDOW_AUTOSIZE);
	createTrackbar("threshold", "binarize", &thresh, MAX_THRESH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}