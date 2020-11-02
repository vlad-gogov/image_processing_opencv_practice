#include "Metrics.h"

double Immse(const Mat& firstImage, const Mat& secondImage)
{
	if (firstImage.size() != secondImage.size())
		throw "Invalid size";
	double result = 0;
	for (int i = 0; i < firstImage.rows; i++)
	{
		for (int j = 0; j < firstImage.cols; j++)
		{
			//std::cout << firstImage.at<double>(i, j) << std::endl;
			int temp1 = (firstImage.at<Vec3b>(i, j)[0] + firstImage.at<Vec3b>(i, j)[1] + firstImage.at<Vec3b>(i, j)[2]);
			int temp2 = (secondImage.at<Vec3b>(i, j)[0] + secondImage.at<Vec3b>(i, j)[1] + secondImage.at<Vec3b>(i, j)[2]);
			int temp = temp1 - temp2;
			result += temp * temp;
		}
	}
	result /= (firstImage.cols * firstImage.rows / 3);
	return result;
}