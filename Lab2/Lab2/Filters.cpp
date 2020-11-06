#include "Filters.h"

Mat median(Mat& image, int radius)
{
	if (image.channels() != 1)
	{
		throw "The image contains more than 1 channel.";
	}
	if (radius < 1)
	{
		throw "Invalid radius.";
	}
	Mat result(image.size(), image.type());
	int matrixSize = (2 * radius + 1) * (2 * radius + 1);
	uchar* colors = new uchar[matrixSize];
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			int k = 0;
			for (int i = -radius; i <= radius; i++)
			{
				for (int j = -radius; j <= radius; j++)
				{
					int X = clamp(x + j, image.rows - 1, 0);
					int Y = clamp(y + i, image.cols - 1, 0);
					uchar color = image.at<uchar>(X, Y);
					colors[k++] = color;
				}
			}
			std::sort(colors, colors + matrixSize);
			result.at<uchar>(x,y) = colors[matrixSize / 2];
		}
	}
	return result;
}

Mat gaussian(Mat& image, int radius, int sigma)
{
	if (image.channels() != 1)
	{
		throw "The image contains more than 1 channel.";
	}
	if (radius < 1)
	{
		throw "Invalid radius.";
	}
	Mat result(image.size(), image.type());
	int size = (2 * radius + 1);
	int matrixSize = size * size;
	float* matrix = new float[matrixSize];
	float norm = 0;

	for (int i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			int idx = (i + radius) * size + (j + radius);
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

	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			uchar resultColor = 0;
			for (int i = -radius; i <= radius; i++)
			{
				for (int j = -radius; j <= radius; j++)
				{
					int idx = (i + radius) * size + j + radius;
					int X = clamp(x + j, image.rows - 1, 0);
					int Y = clamp(y + i, image.cols - 1, 0);
					uchar color = image.at<uchar>(X, Y);
					resultColor += color * matrix[idx];
				}
			}
			result.at<uchar>(x, y) = resultColor;
		}
	}
	return result;
}
