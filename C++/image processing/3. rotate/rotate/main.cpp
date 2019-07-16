#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int argc, char* argv[])
{

	std::string str = "..//..//img//bird.jpg";
	Mat img = imread(str, IMREAD_ANYCOLOR);

	Mat rot_mat30 = getRotationMatrix2D(Point2f(img.cols / 2.0, img.rows / 2.0), 30, 1.0);   // 角度正的為逆時鐘轉
	Mat rot_matminus30 = getRotationMatrix2D(Point2f(img.cols / 2.0, img.rows / 2.0), -30, 1.0);

	Mat img30, imgminus30;
	warpAffine(img, img30, rot_mat30, Size(img.cols, img.rows));
	warpAffine(img, imgminus30, rot_matminus30, Size(img.cols, img.rows));

	Mat img90, img180, img270;
	rotate(img, img90, ROTATE_90_CLOCKWISE);
	rotate(img, img180, ROTATE_180);
	rotate(img, img270, ROTATE_90_COUNTERCLOCKWISE);

	imshow("Org", img);
	imshow("逆時鐘轉30", img30);
	imshow("順時鐘轉30", imgminus30); 
	imshow("轉90", img90);    // 順時鐘
	imshow("轉180", img180);
	imshow("轉270", img270);
	waitKey(0);
	return 0;
}