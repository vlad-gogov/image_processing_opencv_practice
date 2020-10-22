#pragma once
#include "Base_Matrix_filter.h"
#include <vector>

class Dynamic_Matrix_filter : public Base_Matrix_filter
{
protected:
	Dynamic_Matrix_filter(int matrixRadius_ = 1);
	virtual Vec3b calculatePropertyColor(const Vec3b* colors, int colorsCount) const;
	virtual Vec3b calculateNewPixelColor(const Mat& image, int x, int y) const;
	virtual int calculateProperty(int* values, int valuesCount) const;
};

