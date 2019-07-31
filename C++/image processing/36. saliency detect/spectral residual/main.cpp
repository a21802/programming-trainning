#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;
void fft2Image(InputArray _src, OutputArray _dst);
void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum);
Mat phaseSpectrum(Mat _srcFFT);

int main(int argc, char* argv[])
{
	string str = "..//..//img//clock.jpg";
	Mat image = imread(str, IMREAD_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("org", image);
	Mat fImage;
	image.convertTo(fImage, CV_64FC1, 1.0 / 255);

	Mat fft2;
	fft2Image(fImage, fft2);

	Mat amplitude;
	amplitudeSpectrum(fft2, amplitude);

	Mat logAmplitude;
	cv::log(amplitude + 1.0, logAmplitude);

	Mat meanLogAmplitude;
	cv::blur(logAmplitude, meanLogAmplitude, Size(3, 3), Point(-1, -1));

	Mat spectralResidual = logAmplitude - meanLogAmplitude;

	Mat phase = phaseSpectrum(fft2);

	Mat cosSpectrum(phase.size(), CV_64FC1);
	Mat sinSpectrum(phase.size(), CV_64FC1);

	for (int r = 0; r < phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			cosSpectrum.at<double>(r, c) = cos(phase.at<double>(r, c));
			sinSpectrum.at<double>(r, c) = sin(phase.at<double>(r, c));
		}
	}

	exp(spectralResidual, spectralResidual);
	Mat real = spectralResidual.mul(cosSpectrum);
	Mat imaginary = spectralResidual.mul(sinSpectrum);
	vector<Mat> realAndImag;
	realAndImag.push_back(real);
	realAndImag.push_back(imaginary);
	Mat complex;
	merge(realAndImag, complex);

	Mat ifft2;
	dft(complex, ifft2, DFT_COMPLEX_OUTPUT + DFT_INVERSE);

	Mat ifft2Amp;
	amplitudeSpectrum(ifft2, ifft2Amp);

	pow(ifft2Amp, 2.0, ifft2Amp);

	GaussianBlur(ifft2Amp, ifft2Amp, Size(11, 11), 2.5);

	normalize(ifft2Amp, ifft2Amp, 1.0, 0, NORM_MINMAX);

	pow(ifft2Amp, 0.5, ifft2Amp);

	Mat saliencyMap;
	ifft2Amp.convertTo(saliencyMap, CV_8UC1, 255);
	imshow("Saliency", saliencyMap);

	waitKey(0);
	return 0;
}

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