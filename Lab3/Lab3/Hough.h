#pragma once
#include "OpenCV.h"
#include "Canny.h"

void houghLine(Mat& original, float accuracy = 0.1)
{
    Mat src(original);
    Mat rgb;
    Mat bin;
    Mat phase;

    // ������ ������� ��������
    rgb = Mat(src.size(), 8, 3);
    cvtColor(src, rgb, COLOR_GRAY2BGR);

    // �������� �������� - ��� ��������
    bin = Mat(src.size(), CV_8U, 1);
    CannyEdgeDetector(src, bin, 10, 100);

    // ������������ ���������� �� ������ ��������� - ��� ����� ���������
    int RMax = cvRound(sqrt((double)(src.cols * src.cols + src.rows * src.rows)));

    // �������� ��� �������� �������� ������������ ���� (r, f)
    // 0 < r < RMax
    // 0 < f < 2*PI
    phase = Mat(Size(RMax, 180), CV_16U, 1);
    phase.zeros(Size(RMax, 180), 0);

    int x = 0, y = 0, r = 0, f = 0;
    float theta = 0;

    // ����������� �� �������� ����������� ��������
    for (y = 0; y < bin.rows; y++) {
        uchar* ptr = (uchar*)(bin.data + y * bin.step);
        for (x = 0; x < bin.cols; x++) {
            if (ptr[x] > 0) { // ��� ������� �������?
                // ���������� ��� ��������� ������, ������� ����� 
                // ��������� ����� ��� �����
                for (f = 0; f < 180; f++) { //���������� ��� ��������� ���� �������
                    short* ptrP = (short*)(phase.data + f * phase.step);
                    for (r = 0; r < RMax; r++) { // ���������� ��� ��������� ���������� �� ������ ���������
                        theta = f * CV_PI / 180.0; // ��������� ������� � �������

                        // ���� ������� ��������� ���������� ������� (�������� ������ �������)
                        if (abs(((y)*sin(theta) + (x)*cos(theta)) - r) < accuracy) {
                            ptrP[r]++; // ����������� ������� ��� ���� ����� �������� ������������.
                        }
                    }
                }
            }
        }
    }

    // �������� ������� ��������
    Mat phaseImage = Mat(Size(phase.cols * 3, phase.cols * 3), CV_16U, 1);
    phase = Mat(Size(phase.cols * 3, phase.cols * 3), phase.type());

    // �������� ����� �������� ������������ ������� ������� ���������� ����� ���������
    unsigned int MaxPhaseValue = 0;
    float Theta = 0;

    int R = 0;
    for (f = 0; f < 180; f++) { //���������� ��� ��������� ���� �������
        short* ptrP = (short*)(phase.data + f * phase.step);
        for (r = 0; r < RMax; r++) { // ���������� ��� ��������� ���������� �� ������ ���������
            if (ptrP[r] > MaxPhaseValue) {
                MaxPhaseValue = ptrP[r];
                Theta = f;
                R = r;
            }
        }
    }

#if 1
    //printf("[M] %d\n", MaxPhaseValue);

    // ����������
    float scaler = 0xFFFFFFFF / (float)MaxPhaseValue;
    for (y = 0; y < phaseImage.rows; y++) {
        short* ptr = (short*)(phaseImage.data + y * phaseImage.step);
        for (x = 0; x < phaseImage.cols; x++) {
            ptr[x] *= scaler;
        }
    }
    //cvNamedWindow("phaseImage2", 1);
#endif

    // ������ ����� �� ������ ���  R, Teta ������� �������� � ���������� ��������������
    Theta = Theta * CV_PI / 180.0;
    for (y = 0; y < rgb.rows; y++) {
        uchar* ptr = (uchar*)(rgb.data + y * rgb.step);
        for (x = 0; x < rgb.cols; x++) {
            if (cvRound(((y)* sin(Theta) + (x)* cos(Theta))) == R) {
                ptr[3 * x] = 0;
                ptr[3 * x + 1] = 0;
                ptr[3 * x + 2] = 255;
            }
        }
    }

    imshow("line", rgb);
}
