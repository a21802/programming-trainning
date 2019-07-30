#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<map>
#include<iostream>
using namespace std;
using namespace cv;

map<vector<int>, vector<Point>> HTLine(Mat I, Mat& accumulator, float stepTheta = 1, float stepRho = 1)
{

	int rows = I.rows;
	int cols = I.cols;

	int L = round(sqrt(pow(rows - 1, 2.0) + pow(cols - 1, 2.0))) + 1;

	int numtheta = int(180.0 / stepTheta);
	int numRho = int(2 * L / stepRho + 1);
	accumulator = Mat::zeros(Size(numtheta, numRho), CV_32SC1);

	map<vector<int>, vector<Point>> lines;
	for (int i = 0; i < numRho; i++)
	{
		for (int j = 0; j < numtheta; j++)
		{
			lines.insert(make_pair(vector<int>(j, i), vector<Point>()));
		}
	}

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (I.at<uchar>(Point(x, y)) == 255)
			{
				for (int m = 0; m < numtheta; m++)
				{

					float rho1 = x * cos(stepTheta * m / 180.0 * CV_PI);
					float rho2 = y * sin(stepTheta * m / 180.0 * CV_PI);
					float rho = rho1 + rho2;

					int n = int(round(rho + L) / stepRho);

					accumulator.at<int>(n, m) += 1;

					lines.at(vector<int>(m, n)).push_back(Point(x, y));
				}
			}
		}
	}
	return lines;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//img10.jpg";
	Mat img = imread(str, IMREAD_GRAYSCALE);

	Mat edge;
	Canny(img, edge, 50, 200);

	Mat accu;
	map<vector<int>, vector<Point>> lines;
	lines = HTLine(edge, accu);

	double maxValue;
	minMaxLoc(accu, NULL, &maxValue, NULL, NULL);

	Mat grayAccu;
	accu.convertTo(grayAccu, CV_8UC1, 1.0 / maxValue * 255);
	grayAccu = grayAccu.t();
	imshow("計數器灰階顯示", grayAccu);
	//imwrite("grayAccu.jpg", grayAccu);

	int vote = 150;
	for (int r = 1; r < accu.rows - 1; r++)
	{
		for (int c = 1; c < accu.cols - 1; c++)
		{
			int current = accu.at<int>(r, c);

			if (current > vote)
			{

				int lt = accu.at<int>(r - 1, c - 1);
				int t = accu.at<int>(r - 1, c);
				int rt = accu.at<int>(r - 1, c + 1);
				int l = accu.at<int>(r, c - 1);
				int right = accu.at<int>(r, c + 1);
				int lb = accu.at<int>(r + 1, c - 1);
				int b = accu.at<int>(r - 1, c);
				int rb = accu.at<int>(r + 1, c + 1);

				if (current > lt && current > t && current > rt
					&& current > l && current > right &&
					current > lb && current > b && current > rb)
				{
					vector<Point> line = lines.at(vector<int>(c, r));
					int s = line.size();

					cv::line(img, line.at(0), line.at(s - 1), Scalar(255), 2);
				}
			}
		}
	}
	imshow("img", img);
	waitKey(0);
}