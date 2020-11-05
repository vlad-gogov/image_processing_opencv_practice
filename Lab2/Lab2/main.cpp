#include "OpenCV.h"
#include "Median_filter.h"
#include "Gaussian_filter.h"
#include "Noise_filter.h"
#include "Timer.h"


int main()
{
    Mat image = imread("image.jpg");

    if (image.data == nullptr)
    {
        return 1;
    }

    Mat grey_image;
    cvtColor(image, grey_image, COLOR_RGB2GRAY);
    namedWindow("Grey image", WINDOW_AUTOSIZE);
    imshow("Grey image", grey_image);

    Mat noise;

    try
    {
        noise = createSaltAndPepper(grey_image);
    }
    catch (...)
    {
        std::cout << "error";
    }
    namedWindow("Noise image", WINDOW_AUTOSIZE);
    imshow("Noise image", noise);

    Gaussian_filter gaussianFilter;
    Timer t1;
    Mat gaussianFilterImage = gaussianFilter.calculateNewImagePixMap(noise);
    std::cout << "gaussianFilter time: " << t1.elapsed() << std::endl;
    imwrite("image/gaussianFilter.jpg", gaussianFilterImage);

    Median_filter medianFilter(3);
    t1.reset();
    Mat medianFilterImage = medianFilter.calculateNewImagePixMap(noise);
    std::cout << "medianFilter time: " << t1.elapsed() << std::endl;
    imwrite("image/medianFilter.jpg", medianFilterImage);

    Mat openCVMedian;
    t1.reset();
    medianBlur(noise, openCVMedian, 3);
    std::cout << "openCVMedian time: " << t1.elapsed() << std::endl;
    imwrite("image/openCVMedian.jpg", openCVMedian);

    waitKey(555555555555555);
}
