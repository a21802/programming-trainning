#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	double fResize_fac = 0.5;

	string str = "..//..//img//bird.jpg";
	Mat I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return -1;

	//¥é®gÂà´«
	Mat s = (Mat_<float>(2, 3) << fResize_fac, 0, 0, 0, fResize_fac, 0);
	//             means  [x'] = [0.5  0 ][x] + [0] 
	//                    [y'] = [ 0  0.5][y]   [0] 

	Mat dst1;
	warpAffine(I, dst1, s, Size(I.cols * fResize_fac, I.rows * fResize_fac));

	Mat dst2;
	resize(I, dst2, Size(), fResize_fac, fResize_fac);
	imshow("Org", I);
	//namedWindow("resize", WINDOW_GUI_EXPANDED);
	imshow("warpAffine", dst1);
	imshow("resize", dst2);

	bool isExit = false;
	while (!isExit) {
		char c = waitKey(0);
		switch (c) {
		case '\x1b':
			cout << "exit......" << endl;
			isExit = true;
		}
	}
	destroyAllWindows();

	//waitKey(0);
	system("pause");
	return 0;
}