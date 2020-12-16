#include "OpenCV.h"
using namespace cv;
using namespace std;

void antiThresh(Mat &src, Mat &dst, int Thresh);
void doWatershed();
void myWatershed(Mat src, Mat gray, int thres);
void resizeimg_show(Mat src, Size dsize, string name);
void showpart_img(Mat src, int x_start, int y_start, Size window, string name);
Mat LBP(Mat src);
