#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace cv;
int main(int argc, char* argv[])
{
	std::string str = "..//..//img//bird.jpg";
	Mat I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return -1;


	Mat s = (Mat_<float>(2, 3) << 0.5, 0, 0, 0, 0.5, 0);
	Mat dst1;
	warpAffine(I, dst1, s, Size(I.cols / 2, I.rows / 2));

	Mat dst2;
	resize(I, dst2, Size(I.cols / 2, I.rows / 2), 0.5, 0.5);
	imshow("I", I);
	imshow("warpAffine", dst1);
	imshow("resize", dst2);
	waitKey(0);
	return 0;
}