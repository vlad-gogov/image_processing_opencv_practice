#include "Filter.h"

bool Filter::validCoordinate(Point2i point, int width, int height) const
{
	bool ValidX = ((point.x >= 0) && (point.x <= width - 1));
	bool ValidY = ((point.y >= 0) && (point.y <= height - 1));
	return ValidX && ValidY;
}

Vec3b Filter::colorSubstraction(Vec3b first, Vec3b second) const
{
	int red = clamp(first[0] - second[0], 255, 0);
	int green = clamp(first[1] - second[1], 255, 0);
	int blue = clamp(first[2] - second[2], 255, 0);
	return Vec3b(red, green, blue);
}
