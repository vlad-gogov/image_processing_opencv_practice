#include "OpenCV.h"
#include "ShadeOfGray.h"
#include "Metrics.h"
#include "ColorModel.h"

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("image.jpg");

    if (image.data == nullptr)
    {
        return 1;
    }

    // Shade of Gray
    //TestGray(image);
    //Mat AverageImage = Average(image);
    //namedWindow("Average image", WINDOW_AUTOSIZE);
    //imshow("Average image", AverageImage);
    //Mat BGR2GRAYImage;
    //cvtColor(image, BGR2GRAYImage, COLOR_BGR2GRAY, 0);
    //namedWindow("Color BGR2GRAY image", WINDOW_AUTOSIZE);
    //imshow("Color BGR2GRAY image", BGR2GRAYImage);

    //Metrics

    //double err = Immse(AverageImage, BGR2GRAYImage);
    //std::cout << err;

    //Color Model
    TestColorYUV(image);

    waitKey(3111111111);
    return 0;
}