#pragma once

#include "OpenCV.h"

Mat BgrToYuv(Mat image);
Mat YuvToBgr(Mat image);
Mat BrightnessUpBGR(Mat image, int temp);
Mat BrightnessUpYUV(Mat image, int temp);

void TestColorYUV(Mat& image);
void TimeTest(Mat image);