#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat guidedFilter(Mat I, Mat p, int r, float eps)
{

	int rows = I.rows;
	int cols = I.cols;

	Mat mean_I, mean_p;
	boxFilter(I, mean_I, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	boxFilter(p, mean_p, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));

	Mat Ip = I.mul(p);
	Mat mean_Ip;
	boxFilter(Ip, mean_Ip, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));

	Mat cov_Ip = mean_Ip - mean_I.mul(mean_p);

	Mat mean_II;
	boxFilter(I.mul(I), mean_II, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));

	Mat var_I = mean_II - mean_I.mul(mean_I);
	Mat a = cov_Ip / (var_I + eps);
	Mat b = mean_p - a.mul(mean_I);

	Mat mean_a, mean_b;
	boxFilter(a, mean_a, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	boxFilter(b, mean_b, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	Mat q = mean_a.mul(I) + mean_b;
	return q;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img5.jpg";
	Mat I = imread(str, IMREAD_GRAYSCALE);
	Mat p = imread(str, IMREAD_GRAYSCALE);
	//Mat p;
	//I.copyTo(p);
	if (!I.data || !p.data)
		return -1;

	imshow("I", I);
	//imwrite("I.jpg", I);

	Mat fI, fp;
	I.convertTo(fI, CV_64FC1, 1.0 / 255);
	p.convertTo(fp, CV_64FC1, 1.0 / 255);

	Mat q = guidedFilter(fI, fp, 8, 0.001);
	imshow("q", q);
	Mat resultq;
	q.convertTo(resultq, CV_8UC1, 255, 0);
	//imwrite("q71.jpg", resultq);

	Mat I_enhanced = (fI - q) * 10 + q;
	normalize(I_enhanced, I_enhanced, 1, 0, NORM_MINMAX, CV_32FC1);
	imshow("I_enhanced", I_enhanced);
	//Mat resultEnhanced;
	//I_enhanced.convertTo(resultEnhanced, CV_8UC1, 255, 0);
	//imwrite("en.jpg", resultEnhanced);
	waitKey(0);
	return 0;
}