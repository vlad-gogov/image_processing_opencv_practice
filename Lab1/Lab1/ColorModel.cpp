#include "ColorModel.h"
#include "Metrics.h"
#include <ctime>

template<typename T>
T clamp(T x, T max, T min)
{
	if (x > max)
		x = max;
	else if (x < min)
		x = min;
	return x;
}

Mat BgrToYuv(Mat& image)
{
	Mat result(image.size(), CV_8UC3);
	int cols = result.cols, rows = result.rows;
	uchar MaxY = 235, MinY = 16, MaxU = 240, MinU = 16;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			uchar Y;
			short U, V;
			Y = (image.at<Vec3b>(i, j)[2] * 65.738 + image.at<Vec3b>(i, j)[1] * 129.057 + image.at<Vec3b>(i, j)[0] * 25.064) / 256 ;
			U = (image.at<Vec3b>(i, j)[2] * (-37.945) + image.at<Vec3b>(i, j)[1] * (-74.494) + image.at<Vec3b>(i, j)[0] * 112.439) / 256;
			V = (image.at<Vec3b>(i, j)[2] * 112.439 + image.at<Vec3b>(i, j)[1] * (-94.154) + image.at<Vec3b>(i, j)[0] * (-18.285)) / 256;
			result.at<Vec3b>(i, j)[0] = clamp<unsigned short>(Y + 16, MaxY, MinY);
			result.at<Vec3b>(i, j)[1] = clamp<unsigned short>(U + 128, MaxU, MinU);
			result.at<Vec3b>(i, j)[2] = clamp<unsigned short>(V + 128, MaxU, MinU);
		}
	}
	return result;
}

Mat YuvToBgr(Mat& image)
{
	Mat result(image.size(), CV_8UC3);
	int cols = image.cols, rows = image.rows;
	uchar Max = 255, Min = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			uchar R, G, B;
			R = (image.at<Vec3b>(i, j)[0] - 16) * 255 / 219 + image.at<Vec3b>(i, j)[1] * 0 + (image.at<Vec3b>(i, j)[2] - 128) * 255 / 224 * 1.042;
			G = ((image.at<Vec3b>(i, j)[0] - 16) * 255 / 219 + (image.at<Vec3b>(i, j)[1] - 128) * 255 / 224 * 1.772 * 0.114 / 0.587 + (image.at<Vec3b>(i, j)[2] - 128) * 255 / 224 * 1.042 * 0.299 / 0.587);
			B = ((image.at<Vec3b>(i, j)[0] - 16) * 255 / 219 + (image.at<Vec3b>(i, j)[1] - 128) * 255 / 224 * 1.772 + image.at<Vec3b>(i, j)[2] * 0);
			result.at<Vec3b>(i, j)[2] = clamp<uchar>(R, Max, Min);
			result.at<Vec3b>(i, j)[1] = clamp<uchar>(G, Max, Min);
			result.at<Vec3b>(i, j)[0] = clamp<uchar>(B, Max, Min);
		}
	}
	return result;
}

Mat BrightnessUpBGR(Mat& image, int temp)
{
	Mat result(image.size(), CV_8UC3);
	int cols = image.cols, rows = image.rows;
	int Max = 255, Min = 0; int R, G, B;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.at<Vec3b>(i, j)[0] = clamp<unsigned short>(image.at<Vec3b>(i, j)[0] + temp, Max, Min);
			result.at<Vec3b>(i, j)[1] = clamp<unsigned short>(image.at<Vec3b>(i, j)[1] + temp, Max, Min);
			result.at<Vec3b>(i, j)[2] = clamp<unsigned short>(image.at<Vec3b>(i, j)[2] + temp, Max, Min);
		}
	}
	return result;
}

Mat BrightnessUpYUV(Mat& image, uchar temp)
{
	Mat result(image.size(), image.type());
	int cols = image.cols, rows = image.rows;
	uchar Max = 235, Min = 16;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.at<Vec3b>(i, j)[0] = clamp<uchar>(image.at<Vec3b>(i, j)[0] + temp, Max, Min);
			result.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1];
			result.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];
		}
	}
	return result;
}

void TimeTest(Mat& image)
{
	Mat result;
	float start = clock();
	for (int i = 0; i < 1000; i++)
	{
		result = BgrToYuv(image);
	}
	float end = clock();
	float t = (end - start) / CLOCKS_PER_SEC;

	std::cout << "Our time: " << t << std::endl;

	start = clock();
	for (int i = 0; i < 1000; i++)
	{
		cvtColor(image, result, COLOR_RGB2YUV, 0);
	}
	end = clock();
	t = (end - start) / CLOCKS_PER_SEC;

	std::cout << "OpenCV time: " << t << std::endl;
}

void TestColorYUV(Mat& image)
{
	Mat YUVImage = BgrToYuv(image);
	namedWindow("YUV image", WINDOW_AUTOSIZE);
	imshow("YUV image", YUVImage);

	Mat BrigYUVImage = BrightnessUpYUV(YUVImage, 20);
	namedWindow("Brig YUV image", WINDOW_AUTOSIZE);
	imshow("Brig YUV image", BrigYUVImage);

	Mat BGRImage = YuvToBgr(YUVImage);
	namedWindow("BGR image", WINDOW_AUTOSIZE);
	imshow("BGR image", BGRImage);

	Mat BrigBGRImage = BrightnessUpBGR(BGRImage, 50);
	namedWindow("Brig BGR image", WINDOW_AUTOSIZE);
	imshow("Brig BGR image", BrigBGRImage);

	//OpenCV convertation 
	Mat BGR2YUVImage;
	cvtColor(image, BGR2YUVImage, COLOR_RGB2YUV, 0);
	namedWindow("Color BGR2YUV image", WINDOW_AUTOSIZE);
	imshow("Color BGR2YUV image", BGR2YUVImage);
	Mat YVI2BGRImage;
	cvtColor(BGR2YUVImage, YVI2BGRImage, COLOR_YUV2RGB, 0);
	namedWindow("Color YUV2BGR image", WINDOW_AUTOSIZE);
	imshow("Color YUV2BGR image", YVI2BGRImage);

	float err1 = Immse(YUVImage, BGR2YUVImage);
	float err2 = Immse(BGRImage, YVI2BGRImage);

	std::cout << "BGR to YUV: " << err1 << std::endl << "YUV to BGR: " << err2 << std::endl;
}