#pragma once
#include "Matrix_filter.h"

class Gaussian_blur_filter : public Matrix_filter
{
public:
	Gaussian_blur_filter(int radius = 3, int sigma = 2);
	~Gaussian_blur_filter() = default;
};


