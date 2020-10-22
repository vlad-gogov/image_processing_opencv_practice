#include "Median_filter.h"

Median_filter::Median_filter(int radius) : Dynamic_Matrix_filter(radius) {}

int Median_filter::calculateProperty(int* values, int valuesCount) const
{
	std::sort(values, values + valuesCount);
	return values[valuesCount / 2];
}