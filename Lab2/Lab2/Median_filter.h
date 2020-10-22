#pragma once
#include "Dynamic_Matrix_filter.h"

class Median_filter : public Dynamic_Matrix_filter
{
protected:
	int calculateProperty(int* values, int valuesCount) const;

public:
	Median_filter(int radius = 1);
	~Median_filter() = default;
};

