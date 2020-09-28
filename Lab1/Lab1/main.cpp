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

    //Metrics
    //double err = Immse(AverageImage, BGR2GRAYImage);
    //std::cout << err;

    //Color Model
    TestColorYUV(image);

    waitKey(3111111111);
    return 0;
}