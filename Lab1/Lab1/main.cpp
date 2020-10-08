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
    TestGray(image);

    //Color Model
    TestColorYUV(image);
    TimeTest(image);

    waitKey(3111111111);
    return 0;
}