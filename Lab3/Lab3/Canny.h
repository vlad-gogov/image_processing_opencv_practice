#pragma once
#include "OpenCV.h"

void CannyEdgeDetector(Mat &src, Mat &edges, int upperThresh, int lowerThresh);
void nonMaximumSuppression(Mat &magnitudeImage, Mat &directionImage);
void edgeDetect(Mat &magnitude, int tUpper, int tLower, Mat &edges);
void followEdges(int x, int y, Mat &magnitude, int tUpper, int tLower, Mat &edges);