#include "ColorModel.h"

uchar clamp(uchar x, uchar max, uchar min)
{
	if (x > max)
		x = max;
	else if (x < min)
		x = min;
	return x;
}

Mat BgrToYuv(Mat& image)
{
	Mat result(image.size(), image.type());
	//float Kr = 0.299, Kb = 0.114;
	int cols = image.cols, rows = image.rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//Vec3b yuv;
			/*yuv[0] =  Kr * image.at<Vec3b>(i, j)[2] + (1 - Kr - Kb) * image.at<Vec3b>(i, j)[1] + Kb * image.at<Vec3b>(i, j)[0];
			yuv[1] = image.at<Vec3b>(i, j)[0] - yuv[0];
			yuv[2] = image.at<Vec3b>(i, j)[2] - yuv[0];*/
			// 120
			result.at<Vec3b>(i, j)[2] = clamp(0.299 * image.at<Vec3b>(i, j)[2] + 0.587 * image.at<Vec3b>(i, j)[1] + 0.114 * image.at<Vec3b>(i, j)[0], 255, 0);
			result.at<Vec3b>(i, j)[1] = clamp(-0.147 * image.at<Vec3b>(i, j)[2] + -0.289 * image.at<Vec3b>(i, j)[1] + 0.437 * image.at<Vec3b>(i, j)[0], 111.44, -111.44);
			result.at<Vec3b>(i, j)[0] = clamp(0.615 * image.at<Vec3b>(i, j)[2] + -0.515 * image.at<Vec3b>(i, j)[1] + -0.09 * image.at<Vec3b>(i, j)[0], 156.83, -154.49);
		}
	}
	return result;
	//Mat R(image.size(), image.type()), G(image.size(), image.type()), B(image.size(), image.type()),
	//    Max(image.size(), image.type()), Min(image.size(), image.type());
}

Mat YuvToBgr(Mat& image)
{
	Mat result(image.size(), image.type());
	int cols = image.cols, rows = image.rows;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{ // Y = 2 U = 1 V = 0
			result.at<Vec3b>(i, j)[2] = clamp(image.at<Vec3b>(i, j)[2] + -0.048 * image.at<Vec3b>(i, j)[1] + 1.138 * image.at<Vec3b>(i, j)[0], 255, 0);
			result.at<Vec3b>(i, j)[1] = clamp(image.at<Vec3b>(i, j)[2] + -0.37 * image.at<Vec3b>(i, j)[1] + -0.579 * image.at<Vec3b>(i, j)[0], 111.44, -111.44);
			result.at<Vec3b>(i, j)[0] = clamp(image.at<Vec3b>(i, j)[2] + 2.028 * image.at<Vec3b>(i, j)[1], 156.83, -154.49);
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
	Mat BGR2YUVImage;
	cvtColor(image, BGR2YUVImage, COLOR_BGR2YUV, 0);
	namedWindow("Color BGR2YUV image", WINDOW_AUTOSIZE);
	imshow("Color BGR2YUV image", BGR2YUVImage);
}