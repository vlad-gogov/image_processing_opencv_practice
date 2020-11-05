#pragma once
#include "Matrix_filter.h"

class Gaussian_filter : public Matrix_filter
{
public:
	Gaussian_filter(int radius = 3, int sigma = 2);
	~Gaussian_filter() = default;
};


