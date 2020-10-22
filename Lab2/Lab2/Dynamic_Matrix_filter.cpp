#include "Dynamic_Matrix_filter.h"

Dynamic_Matrix_filter::Dynamic_Matrix_filter(int matrixRadius_) : Base_Matrix_filter(matrixRadius_) {}

Vec3b Dynamic_Matrix_filter::calculateNewPixelColor(const Mat& image, int x, int y) const
{
	Vec3b* colors = new Vec3b[matrixSize];
	int k = 0;
	for (int i = -matrixRadius; i <= matrixRadius; i++)
		for (int j = -matrixRadius; j <= matrixRadius; j++)
		{
			int X = clamp(x + j, image.rows - 1, 0);
			int Y = clamp(y + i, image.cols - 1, 0);
			Vec3b color = image.at<Vec3b>(i, j);
			colors[k++] = color;
		}
	Vec3b color = calculatePropertyColor(colors, matrixSize);
	delete[] colors;
	return color;
}

Vec3b Dynamic_Matrix_filter::calculatePropertyColor(const Vec3b* colors, int colorsCount) const
{
	int* red = new int[colorsCount];
	int* green = new int[colorsCount];
	int* blue = new int[colorsCount];
	for (int i = 0; i < colorsCount; i++)
	{
		red[i] = colors[i][2];
		green[i] = colors[i][1];
		blue[i] = colors[i][0];
	}
	int redMaximum = calculateProperty(red, colorsCount);
	int greenMaximum = calculateProperty(green, colorsCount);
	int blueMaximum = calculateProperty(blue, colorsCount);

	redMaximum = clamp(redMaximum, 255, 0);
	greenMaximum = clamp(greenMaximum, 255, 0);
	blueMaximum = clamp(blueMaximum, 255, 0);

	delete[] red;
	delete[] green;
	delete[] blue;

	return Vec3b(redMaximum, greenMaximum, blueMaximum);
}

int Dynamic_Matrix_filter::calculateProperty(int* values, int valuesCount) const
{
	return 0;
}