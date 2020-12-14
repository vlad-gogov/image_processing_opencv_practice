#pragma once
#include "OpenCV.h"
#include "Canny.h"

void houghLine(Mat& original, float accuracy = 0.1)
{
    Mat src(original);
    Mat rgb;
    Mat bin;
    Mat phase;

    // заведём цветную картинку
    rgb = Mat(src.size(), 8, 3);
    cvtColor(src, rgb, COLOR_GRAY2BGR);

    // бинарная картинка - для контуров
    bin = Mat(src.size(), CV_8U, 1);
    CannyEdgeDetector(src, bin, 10, 100);

    // максимальное расстояние от начала координат - это длина диагонали
    int RMax = cvRound(sqrt((double)(src.cols * src.cols + src.rows * src.rows)));

    // картинка для хранения фазового пространства Хафа (r, f)
    // 0 < r < RMax
    // 0 < f < 2*PI
    phase = Mat(Size(RMax, 180), CV_16U, 1);
    phase.zeros(Size(RMax, 180), 0);

    int x = 0, y = 0, r = 0, f = 0;
    float theta = 0;

    // пробегаемся по пикселям изображения контуров
    for (y = 0; y < bin.rows; y++) {
        uchar* ptr = (uchar*)(bin.data + y * bin.step);
        for (x = 0; x < bin.cols; x++) {
            if (ptr[x] > 0) { // это пиксель контура?
                // рассмотрим все возможные прямые, которые могут 
                // проходить через эту точку
                for (f = 0; f < 180; f++) { //перебираем все возможные углы наклона
                    short* ptrP = (short*)(phase.data + f * phase.step);
                    for (r = 0; r < RMax; r++) { // перебираем все возможные расстояния от начала координат
                        theta = f * CV_PI / 180.0; // переводим градусы в радианы

                        // Если решение уравнения достаточно хорошее (точность больше заданой)
                        if (abs(((y)*sin(theta) + (x)*cos(theta)) - r) < accuracy) {
                            ptrP[r]++; // увеличиваем счетчик для этой точки фазового пространства.
                        }
                    }
                }
            }
        }
    }

    // увеличим фазовую картинку
    Mat phaseImage = Mat(Size(phase.cols * 3, phase.cols * 3), CV_16U, 1);
    phase = Mat(Size(phase.cols * 3, phase.cols * 3), phase.type());

    // Выбираем точку фазового пространства которая набрала наибольшее число попаданий
    unsigned int MaxPhaseValue = 0;
    float Theta = 0;

    int R = 0;
    for (f = 0; f < 180; f++) { //перебираем все возможные углы наклона
        short* ptrP = (short*)(phase.data + f * phase.step);
        for (r = 0; r < RMax; r++) { // перебираем все возможные расстояния от начала координат
            if (ptrP[r] > MaxPhaseValue) {
                MaxPhaseValue = ptrP[r];
                Theta = f;
                R = r;
            }
        }
    }

#if 1
    //printf("[M] %d\n", MaxPhaseValue);

    // нормировка
    float scaler = 0xFFFFFFFF / (float)MaxPhaseValue;
    for (y = 0; y < phaseImage.rows; y++) {
        short* ptr = (short*)(phaseImage.data + y * phaseImage.step);
        for (x = 0; x < phaseImage.cols; x++) {
            ptr[x] *= scaler;
        }
    }
    //cvNamedWindow("phaseImage2", 1);
#endif

    // Рисуем линию по точкам для  R, Teta которые получили в результате преобразования
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
