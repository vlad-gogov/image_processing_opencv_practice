#pragma once
#include "Filter.h"

class Base_Matrix_filter : public Filter
{
protected:
	int matrixRadius;
	int matrixSize;
	Base_Matrix_filter(int matrixRaduis_ = 1);
	virtual Vec3b calculateNewPixelColor(const Mat& image, int x, int y) const = 0;

public:
	Mat calculateNewImagePixMap(const Mat& image);
};

