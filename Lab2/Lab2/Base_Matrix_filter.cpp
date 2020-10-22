#include "Base_Matrix_filter.h"

Base_Matrix_filter::Base_Matrix_filter(int matrixRadius_)
{
	matrixRadius = matrixRadius_;
	matrixSize = (2 * matrixRadius + 1) * (2 * matrixRadius + 1);
}

Mat Base_Matrix_filter::calculateNewImagePixMap(const Mat& image)
{
	Mat result_Image(image);
	for (int x = 0; x < image.rows; x++)
		for (int y = 0; y < image.cols; y++)
		{
			Vec3b photo_color = calculateNewPixelColor(image, x, y);
			result_Image.at<Vec3b>(x, y) = photo_color;
		}
	return result_Image;
}