#include "Matrix_filter.h"

Matrix_filter::Matrix_filter(int matrixradius_) : Base_Matrix_filter(matrixradius_)
{
	matrix = new float[matrixSize];
}

Vec3b Matrix_filter::calculateNewPixelColor(const Mat& photo, int x, int y) const
{
	int returnR = 0, returnG = 0, returnB = 0;
	for (int i = -matrixRadius; i <= matrixRadius; i++)
		for (int j = -matrixRadius; j <= matrixRadius; j++)
		{
			int idx = (i + matrixRadius) * (2 * matrixRadius + 1) + j + matrixRadius;
			Vec3b color = photo.at<Vec3b>(clamp<int>(x + j, photo.rows - 1, 0), clamp<int>(y + i, photo.cols - 1, 0));
			returnR += color[2] * matrix[idx];
			returnG += color[1] * matrix[idx];
			returnB += color[0] * matrix[idx];
		}
	return Vec3b(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}

Matrix_filter::~Matrix_filter()
{
	delete[] matrix;
}
