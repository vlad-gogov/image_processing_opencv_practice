#include "OpenCV.h"
#include "Noise_filter.h"
#include "Timer.h"
#include "Filters.h"


int main()
{
    Mat image = imread("image.jpg");

    if (image.data == nullptr)
    {
        return 1;
    }

    Mat greyImage;
    cvtColor(image, greyImage, COLOR_RGB2GRAY);
    imwrite("image/Grey.jpg", greyImage);

    Mat noise;
    try
    {
        noise = createSaltAndPepper(greyImage);
    }
    catch (const char* message)
    {
        std::cout << message << std::endl;
    }
    imwrite("image/Noise.jpg", greyImage);
    
    Mat medianImage;
    Timer t1;
    try
    {
        medianImage = median(greyImage, 3);
    }
    catch (const char* message)
    {
        std::cout << message << std::endl;
    }
    std::cout << "Median time: " << t1.elapsed() << std::endl;
    imwrite("image/Median.jpg", medianImage);

    Mat openCVMedian;
    t1.reset();
    medianBlur(noise, openCVMedian, 3);
    std::cout << "openCVMedian time: " << t1.elapsed() << std::endl;
    imwrite("image/openCVMedian.jpg", openCVMedian);

    Mat gaussianImage;
    t1.reset();
    try
    {
        gaussianImage = gaussian(greyImage, 1, 3);
    }
    catch (const char* message)
    {
        std::cout << message << std::endl;
    }
    std::cout << "Gaussian time: " << t1.elapsed() << std::endl;
    imwrite("image/Gaussian.jpg", gaussianImage);

    waitKey(555555555555555);
}
