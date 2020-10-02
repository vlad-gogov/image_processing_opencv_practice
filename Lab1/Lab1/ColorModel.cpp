#include "ColorModel.h"

uchar clamp(uchar x, uchar max, uchar min)
{
	if (x > max)
		x = max;
	else if (x < min)
		x = min;
	return x;
}

float clamp(float x, float max, float min)
{
	if (x > max)
		x = max;
	else if (x < min)
		x = min;
	return x;
}

Mat BgrToYuv(Mat& image)
{
	Mat result(image.size(), CV_32FC3);
	int cols = result.cols, rows = result.rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Vec3f yuv;
			yuv[0] = clamp(0.299f * image.at<Vec3b>(i, j)[0] + 0.587f * image.at<Vec3b>(i, j)[1] + 0.114f * image.at<Vec3b>(i, j)[2], 255.f, 0.f);
			yuv[1] = clamp(0.492f * ((float)image.at<Vec3b>(i, j)[2] - yuv[0]), 125.46f, -125.46f);
			yuv[2] = clamp(0.877f * ((float)image.at<Vec3b>(i, j)[0] - yuv[0]), 156.825f, -156.825f);
		/*	yuv[0] = 0.2126f * image.at<Vec3b>(i, j)[2] + 0.7152f * image.at<Vec3b>(i, j)[1] + 0.0722f * image.at<Vec3b>(i, j)[0];
			yuv[1] = -0.09991f * image.at<Vec3b>(i, j)[2] + -0.33609f * image.at<Vec3b>(i, j)[1] + 0.436f * image.at<Vec3b>(i, j)[0];
			yuv[2] = 0.615f * image.at<Vec3b>(i, j)[2] + -0.55861f * image.at<Vec3b>(i, j)[1] + -0.05639f * image.at<Vec3b>(i, j)[0];*/
			//std::cout << yuv[0] << "|" << yuv[1] << "|" << yuv[2] << std::endl;
			result.at<Vec3f>(i, j)[0] = yuv[0];
			result.at<Vec3f>(i, j)[1] = yuv[1];
			result.at<Vec3f>(i, j)[2] = yuv[2];
		}
	}
	return result;
}

Mat YuvToBgr(Mat& image)
{
	Mat result(image.size(), CV_8UC3);
	int cols = image.cols, rows = image.rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Vec3f yuv;
			yuv[0] = image.at<Vec3f>(i, j)[0] + 1.13983f * image.at<Vec3f>(i, j)[2];
			yuv[1] = image.at<Vec3f>(i, j)[0] + -0.39465f * image.at<Vec3f>(i, j)[1] + -0.58060f * image.at<Vec3f>(i, j)[2];
			yuv[2] = image.at<Vec3f>(i, j)[0] + 2.03211f * image.at<Vec3f>(i, j)[1];
			/*yuv[0] = image.at<Vec3f>(i, j)[0] + 0 * image.at<Vec3f>(i, j)[1] + 1.28033f * image.at<Vec3f>(i, j)[2];
			yuv[1] = image.at<Vec3f>(i, j)[0] + -0.21482f * image.at<Vec3f>(i, j)[1] + -0.38059f * image.at<Vec3f>(i, j)[2];
			yuv[2] = image.at<Vec3f>(i, j)[0] + 2.12798f * image.at<Vec3f>(i, j)[1];*/
			/*std::cout << yuv[0] << "|" << yuv[1] << "|" << yuv[2] << std::endl;*/
			result.at<Vec3b>(i, j)[0] = yuv[0];
			result.at<Vec3b>(i, j)[1] = yuv[1];
			result.at<Vec3b>(i, j)[2] = yuv[2];
		}
	}
	return result;
}

void TestColorYUV(Mat& image)
{
	Mat YUVImage = BgrToYuv(image);
	namedWindow("YUV image", WINDOW_AUTOSIZE);
	imshow("YUV image", YUVImage);
	Mat BGRImage = YuvToBgr(YUVImage);
	namedWindow("BGR image", WINDOW_AUTOSIZE);
	imshow("BGR image", BGRImage);
	//Mat BGR2YUVImage;
	//cvtColor(image, BGR2YUVImage, COLOR_RGB2YUV, 0);
	//namedWindow("Color BGR2YUV image", WINDOW_AUTOSIZE);
	//imshow("Color BGR2YUV image", BGR2YUVImage);
	//Mat YVI2BGRImage;
	//cvtColor(BGR2YUVImage, YVI2BGRImage, COLOR_YUV2RGB, 0);
	//namedWindow("Color YUV2BGR image", WINDOW_AUTOSIZE);
	//imshow("Color YUV2BGR image", YVI2BGRImage);
}