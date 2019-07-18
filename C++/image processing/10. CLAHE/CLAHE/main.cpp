#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

void clahe(Mat &src)
{
	Ptr<CLAHE> clahe = createCLAHE(2, Size(8, 8));

	Mat dst;
	clahe->apply(src, dst);
	imshow("clahe", dst);
	//imwrite("clahe.jpg", dst);
}

void equalHist(Mat &src)
{
	CV_Assert(src.type() == CV_8UC1); // 不相等則跳警告

	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };
	Mat hist;
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	// 累加灰階直方圖
	//Mat zeroCumuMoment = Mat::zeros(Size(256, 1), CV_32SC1);
	//for (int p = 0; p < 256; p++)
	//{
	//	if (p == 0)
	//		zeroCumuMoment.at<int>(0, p) = static_cast<int>(hist.at<float>(0));
	//	else
	//		zeroCumuMoment.at<int>(0, p) = zeroCumuMoment.at<int>(0, p - 1) + static_cast<int>(hist.at<float>(p));
	//}

	// 根據累加直方圖的數值與全圖大小得到一比例關係
	// 根據這比例轉換灰階值
	Mat outPut_q = Mat::zeros(Size(256, 1), CV_8UC1);
	int sum = 0;
	float cofficient = 256.0 / (src.rows * src.cols);
	for (int p = 0; p < 256; p++)
	{
		sum += static_cast<int>(hist.at<float>(p)); // 累加
		float q = cofficient * sum - 1;
		if (q >= 0)
			outPut_q.at<uchar>(0, p) = uchar(floor(q));
		else
			outPut_q.at<uchar>(0, p) = 0;
	}

	Mat euqalHistImage;
	LUT(src, outPut_q, euqalHistImage);
	imshow("equal histogram", euqalHistImage);
}

int main(int argc, char* argv[])
{
	string str = "..//..//img//img4.jpg";
	Mat src = imread(str, IMREAD_GRAYSCALE);
	if (!src.data)
		return -1;

	imshow("org", src);
	clahe(src);
	equalHist(src);

	waitKey(0);
	return 0;
}