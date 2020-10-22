#pragma once
#include "OpenCV.h"

class Filter {
protected:
	Filter() = default;
	~Filter() = default;


	template<typename T> T clamp(T v, int max, int min) const;
	bool validCoordinate(Point2i point, int width, int height) const;
	Vec3b colorSubstraction(Vec3b first, Vec3b right) const;
public:
	virtual Mat calculateNewImagePixMap(const Mat& photo) = 0;
};

template<typename T>
T Filter::clamp(T v, int max, int min) const
{
	if (v > max)
		return max;
	else if (v < min)
		return min;
	return v;
}

