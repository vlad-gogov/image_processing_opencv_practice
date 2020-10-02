#include "Metrics.h"

double Immse(Mat& firstImage, Mat& secondImage)
{
	if (firstImage.size() != secondImage.size())
		return -1;
	double result = 0, temp, temp1, temp2;
	for (int i = 0; i < firstImage.rows - 1; i++)
	{
		for (int j = 0; j < firstImage.cols - 1; j++)
		{
			//std::cout << firstImage.at<double>(i, j) << std::endl;
			temp1 = (firstImage.at<Vec3b>(i, j)[0] + firstImage.at<Vec3b>(i, j)[1] + firstImage.at<Vec3b>(i, j)[2]) / 3;
			temp2 = (secondImage.at<Vec3b>(i, j)[0] + secondImage.at<Vec3b>(i, j)[1] + secondImage.at<Vec3b>(i, j)[2]) / 3;
			temp = temp1 - temp2;
			result += temp * temp;
		}
	}
	result /= (firstImage.cols * firstImage.rows);
	return result;
}