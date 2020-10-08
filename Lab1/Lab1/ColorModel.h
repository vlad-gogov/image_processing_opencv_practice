#pragma once

#include "OpenCV.h"

Mat BgrToYuv(Mat& image);
Mat YuvToBgr(Mat& image);

void TestColorYUV(Mat& image);
void TimeTest(Mat& image);