#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

void fft2Image(InputArray _src, OutputArray _dst)
{

	Mat src = _src.getMat();

	CV_Assert(src.type() == CV_32FC1 || src.type() == CV_64FC1);
	CV_Assert(src.channels() == 1 || src.channels() == 2);
	int rows = src.rows;
	int cols = src.cols;

	Mat padded;
	int rPadded = getOptimalDFTSize(rows);
	int cPadded = getOptimalDFTSize(cols);

	copyMakeBorder(src, padded, 0, rPadded - rows, 0, cPadded - cols, BORDER_CONSTANT, Scalar::all(0));

	dft(padded, _dst, DFT_COMPLEX_OUTPUT);
}

void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum)
{
	CV_Assert(_srcFFT.channels() == 2);
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	magnitude(FFT2Channel[0], FFT2Channel[1], _dstSpectrum);
}

Mat graySpectrum(Mat spectrum)
{
	Mat dst;
	log(spectrum + 1, dst);
	normalize(dst, dst, 0, 1, NORM_MINMAX);
	dst.convertTo(dst, CV_8UC1, 255, 0);
	return dst;
}

Mat phaseSpectrum(Mat _srcFFT)
{

	Mat phase;
	phase.create(_srcFFT.size(), CV_64FC1);

	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);

	for (int r = 0; r < phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			double real = FFT2Channel[0].at<double>(r, c);
			double imaginary = FFT2Channel[1].at<double>(r, c);

			phase.at<double>(r, c) = atan2(imaginary, real);
		}
	}
	return phase;
}
int main(int argc, char* argv[])
{
	string str = "..//..//img//clock.jpg";
	Mat img = imread(str, IMREAD_GRAYSCALE);
	if (!img.data)
		return -1;
	imshow("org", img);

	Mat fImg;
	img.convertTo(fImg, CV_64FC1, 1.0, 0);

	int rows = fImg.rows;
	int cols = fImg.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if ((r + c) % 2)
				fImg.at<double>(r, c) *= -1;
		}
	}

	Mat fft2;
	fft2Image(fImg, fft2);

	Mat ampSpec;
	amplitudeSpectrum(fft2, ampSpec);

	Mat graySpec = graySpectrum(ampSpec);
	imshow("amplitude", graySpec);
	Mat phaSpec = phaseSpectrum(fft2);
	imshow("phase", phaSpec);
	waitKey(0);
	return 0;
}