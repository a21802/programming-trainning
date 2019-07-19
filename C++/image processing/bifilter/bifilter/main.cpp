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

Mat bfltGray(const Mat& image, Size winSize, float sigma_g, float sigma_d)
{
	int winH = winSize.height;
	int winW = winSize.width;

	CV_Assert(winH > 0 && winW > 0);
	CV_Assert(winH % 2 == 1 && winW % 2 == 1);
	if (winH == 1 && winW == 1)
		return image;
	int half_winW = (winW - 1) / 2;
	int half_winH = (winH - 1) / 2;

	Mat closenessWeight = getClosenessWeight(sigma_g, winSize);

	int rows = image.rows;
	int cols = image.cols;

	Mat blfImage = Mat::ones(image.size(), CV_32FC1);

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			double pixel = image.at<double>(r, c);

			int rTop = (r - half_winH) < 0 ? 0 : r - half_winH;
			int rBottom = (r + half_winH) > rows - 1 ? rows - 1 : r + half_winH;
			int cLeft = (c - half_winW) < 0 ? 0 : c - half_winW;
			int cRight = (c + half_winW) > cols - 1 ? cols - 1 : c + half_winW;

			Mat region = image(Rect(Point(cLeft, rTop), Point(cRight + 1, rBottom + 1))).clone();

			Mat similarityWeight;
			pow(region - pixel, 2.0, similarityWeight);
			exp(-0.5 * similarityWeight / pow(sigma_d, 2), similarityWeight);
			similarityWeight /= pow(sigma_d, 2);

			Rect regionRect = Rect(Point(cLeft - c + half_winW, rTop - r + half_winH), Point(cRight - c + half_winW + 1, rBottom - r + half_winH + 1));
			Mat closenessWeightTemp = closenessWeight(regionRect).clone();

			Mat weightTemp = closenessWeightTemp.mul(similarityWeight);
			weightTemp = weightTemp / sum(weightTemp)[0];

			Mat result = weightTemp.mul(region);
			blfImage.at<float>(r, c) = sum(result)[0];
		}
	}
	return blfImage;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img6.png";
	Mat I = imread(str, IMREAD_GRAYSCALE);
	if (!I.data)
		return -1;

	Mat fI;
	I.convertTo(fI, CV_64FC1, 1.0 / 255, 0);

	Mat blfI = bfltGray(fI, Size(33, 33), 19, 0.2);

	imshow("org", I);
	imshow("bifilter", blfI);

	blfI.convertTo(blfI, CV_8U, 255, 0);
	imwrite("blf.jpg", blfI);
	waitKey(0);
	return 0;
}