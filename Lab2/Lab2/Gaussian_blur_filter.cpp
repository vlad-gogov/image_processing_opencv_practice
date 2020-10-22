#include "Gaussian_blur_filter.h"

Gaussian_blur_filter::Gaussian_blur_filter(int radius, int sigma) : Matrix_filter(radius)
{
	const unsigned int size = 2 * matrixRadius + 1;
	float norm = 0;
	for (int i = -matrixRadius; i <= matrixRadius; i++)
	{
		for (int j = -matrixRadius; j <= matrixRadius; j++)
		{
			int idx = (i + matrixRadius) * size + (j + matrixRadius);
			matrix[idx] = exp(-(i * i + j * j) / (sigma * sigma));
			norm += matrix[idx];
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i * size + j] /= norm;
		}
	}
}