#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat getClosenessWeight(double sigma_g, Size size)
{

	int W = size.width;
	int H = size.height;

	int cW = (W - 1) / 2;
	int cH = (H - 1) / 2;

	Mat closenessWeight = Mat::zeros(size, CV_64FC1);
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			double norm2 = pow(double(r - cH), 2.0) + pow(double(c - cW), 2.0);
			double sigma_g2 = 2.0 * pow(sigma_g, 2.0);

			closenessWeight.at<double>(r, c) = exp(-norm2 / sigma_g2);
		}
	}
	return closenessWeight;
}

Mat jointBLF(Mat I, Size size, float sigma_g, float sigma_d, int borterType = BORDER_DEFAULT)
{

	Mat closeWeight = getClosenessWeight(sigma_g, size);

	Mat Ig;
	GaussianBlur(I, Ig, size, sigma_g);

	int cH = (size.height - 1) / 2;
	int cW = (size.width - 1) / 2;

	Mat Ip, Igp;
	copyMakeBorder(I, Ip, cH, cH, cW, cW, borterType);
	copyMakeBorder(Ig, Igp, cH, cH, cW, cW, borterType);

	int rows = I.rows;
	int cols = I.cols;
	int i = 0, j = 0;

	Mat jblf = Mat::zeros(I.size(), CV_64FC1);
	for (int r = cH; r < cH + rows; r++)
	{
		for (int c = cW; c < cW + cols; c++)
		{

			double pixel = Igp.at<double>(r, c);

			Mat region = Igp(Rect(c - cW, r - cH, size.width, size.height));

			Mat similarityWeight;
			pow(region - pixel, 2.0, similarityWeight);
			cv::exp(-0.5 * similarityWeight / pow(sigma_d, 2.0), similarityWeight);

			Mat weight = closeWeight.mul(similarityWeight);

			weight = weight / cv::sum(weight)[0];

			Mat Iregion = Ip(Rect(c - cW, r - cH, size.width, size.height));
			jblf.at<double>(i, j) = sum(Iregion.mul(weight))[0];
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return jblf;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img7.jpg";
	Mat I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return -1;

	Mat fI;
	I.convertTo(fI, CV_64F, 1.0, 0);

	Mat jblf = jointBLF(fI, Size(33, 33), 7, 2);

	Mat jblf8U;
	jblf.convertTo(jblf8U, CV_8U, 1, 0);
	imshow("joint bifilter", jblf8U);
	imshow("org", I);
	waitKey(0);
	return 0;
}