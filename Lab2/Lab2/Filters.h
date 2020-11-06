#pragma once
#include "OpenCV.h"

Mat median(Mat& image, int raduis = 3);
Mat gaussian(Mat& image, int radius = 3, int sigma = 2);

template<typename T>
inline T clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;
	return v;
}
