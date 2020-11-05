#include "Noise_filter.h"

Mat createSaltAndPepper(const Mat& image) 
{
    if (image.channels() != 1)
    {
        throw "dasdads";
    }
    Mat result(image);
    Mat saltpepper_noise = Mat::zeros(image.rows, image.cols, CV_8U);
    cv::randu(saltpepper_noise, 0, 255);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (saltpepper_noise.at<uchar>(i, j) < 30)
            {
                result.at<uchar>(i, j) = 0;
            }
            else if (saltpepper_noise.at<uchar>(i, j) > 225)
            {
                result.at<uchar>(i, j) = 255;
            }
        }
    }
    return result;
}