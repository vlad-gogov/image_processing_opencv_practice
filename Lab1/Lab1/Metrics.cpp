#include "Metrics.h"

double Immse(Mat& firstImage, Mat& secondImage)
{
	if (firstImage.size() != secondImage.size())
		return -1;
	double result = 0, temp;
	for (int i = 0; i < firstImage.rows - 1; i++)
	{
		for (int j = 0; j < firstImage.cols - 1; j++)
		{
			//std::cout << firstImage.at<double>(i, j) << std::endl;
			temp = (firstImage.at<double>(i, j) - secondImage.at<double>(i, j));
			result += temp * temp;
		}
	}
	result /= (firstImage.cols * firstImage.rows);
	return result;
}