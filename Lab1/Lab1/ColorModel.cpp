#include "ColorModel.h"
#include "Metrics.h"
#include "Timer.h"
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

Mat BgrToYuv(Mat image)
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

Mat YuvToBgr(Mat image)
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

Mat BrightnessUpBGR(Mat image, int temp)
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

Mat BrightnessUpYUV(Mat image, int temp)
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

void TimeTest(Mat image)
{
	Mat result;
	Timer t1;
	for (int i = 0; i < 1000; i++)
	{
		result = BrightnessUpBGR(image, 20);
	}
	
	std::cout.precision(5);
	std::cout << "Brightness BGR time: " << t1.elapsed() << " seconds." << std::endl;

	cvtColor(image, result, COLOR_RGB2YUV, 0);
	t1.reset();
	for (int i = 0; i < 1000; i++)
	{
		result = BrightnessUpYUV(result, 20);
	}

	std::cout << "Brightness YUV time: " << t1.elapsed() << " seconds." << std::endl;
}

void TestColorYUV(Mat& image)
{
	std::cout << "------------------Test Color Model------------------" << std::endl;

	Mat YUVImage = BgrToYuv(image);
	namedWindow("YUV image", WINDOW_AUTOSIZE);
	imshow("YUV image", YUVImage);

	Mat BrigYUVImage = BrightnessUpYUV(YUVImage, 20);
	namedWindow("Brig YUV image", WINDOW_AUTOSIZE);
	imshow("Brig YUV image", BrigYUVImage);

	Mat BGRImage = YuvToBgr(YUVImage);
	namedWindow("BGR image", WINDOW_AUTOSIZE);
	imshow("BGR image", BGRImage);

	Mat BrigBGRImage = BrightnessUpBGR(BGRImage, 20);
	namedWindow("Brig BGR image", WINDOW_AUTOSIZE);
	imshow("Brig BGR image", BrigBGRImage);

	//OpenCV convertation 
	Mat BGR2YUVImage;
	cvtColor(image, BGR2YUVImage, COLOR_RGB2YUV, 0);
	namedWindow("Color BGR2YUV image", WINDOW_AUTOSIZE);
	imshow("Color BGR2YUV image", BGR2YUVImage);

	Mat YUV2BGRImage;
	cvtColor(BGR2YUVImage, YUV2BGRImage, COLOR_YUV2RGB, 0);
	namedWindow("Color YUV2BGR image", WINDOW_AUTOSIZE);
	imshow("Color YUV2BGR image", YUV2BGRImage);

	Mat image1 = BrightnessUpBGR(image, 20);
	Mat image2 = YuvToBgr(BrightnessUpYUV(BgrToYuv(image), 20));
	float err1 = Immse(image1, image2);

	cvtColor(image, image2, COLOR_BGR2YUV, 0);
	image2 = BrightnessUpYUV(image2, 20);
	cvtColor(image2, image2, COLOR_YUV2BGR);

	float err2 = Immse(image1, image2);

	//Save image
	//imwrite("image/YUVImage.jpg", YUVImage);
	//imwrite("image/BrigYUVImage.jpg", BrigYUVImage);
	//imwrite("image/BGRImage.jpg", BGRImage);
	//imwrite("image/BrigBGRImage.jpg", BrigBGRImage);
	//imwrite("image/BGR2YUVImage.jpg", BGR2YUVImage);
	//imwrite("image/YUV2BGRImage.jpg", YUV2BGRImage);

	std::cout << "Our convertation: " << err1 << std::endl << "OpenCV: " << err2 << std::endl;
}