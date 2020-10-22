#include "OpenCV.h"
#include "Median_filter.h"
#include "Gaussian_blur_filter.h"


int main()
{
    Mat image = imread("image.jpg");

    if (image.data == nullptr)
    {
        return 1;
    }

    Median_filter medianFilter(2);
    Mat medianFilterImage = medianFilter.calculateNewImagePixMap(image);
    namedWindow("Median image", WINDOW_AUTOSIZE);
    imshow("Median image", medianFilterImage);

    waitKey(555555555555555);
}
