#include "ShadeOfGray.h"

Mat Average(Mat& image)
{
    Mat result(image.size(), image.type());
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            uchar mono = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
            result.at<Vec3b>(i, j)[0] = mono; //Blue
            result.at<Vec3b>(i, j)[1] = mono; //Green
            result.at<Vec3b>(i, j)[2] = mono; //Red
        }
    }
    return result;
}

void TestGray(Mat& image)
{
    Mat AverageImage = Average(image);
    namedWindow("Average image", WINDOW_AUTOSIZE);
    imshow("Average image", AverageImage);
    Mat BGR2GRAYImage;
    cvtColor(image, BGR2GRAYImage, COLOR_BGR2GRAY, 0);
    namedWindow("Color BGR2GRAY image", WINDOW_AUTOSIZE);
    imshow("Color BGR2GRAY image", BGR2GRAYImage);
}