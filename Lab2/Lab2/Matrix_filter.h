#pragma once
#include "Base_Matrix_filter.h"

class Matrix_filter : public Base_Matrix_filter {
protected:
	float* matrix;
	Matrix_filter(int matrixradius_ = 1);
	~Matrix_filter();
	virtual Vec3b calculateNewPixelColor(const Mat& photo, int x, int y) const;
};
