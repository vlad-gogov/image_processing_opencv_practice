#include "OpenCV.h"
#include "Canny.h"
#include "Timer.h"
#include "Watershed.h"

int main()
{
    Mat input;
    input = imread("image.jpg", 0);

    Mat our_edges;
    Mat cv_edges;
    Timer time;
    /**********************************Canny algorithm************************************************/
    time.elapsed();
    CannyEdgeDetector(input, our_edges, 50, 0);
    std::cout << "Our time: " << time.elapsed() << std::endl;

    time.reset();

    time.elapsed();
    Canny(input, cv_edges, 80, 0);
    std::cout << "OpenCV time: " << time.elapsed();
    /**********************************Watershed algorithm************************************************/
    cout << "Watershed result" << endl;
    doWatershed();

    std::string s1 = "edge";
    std::string s2 = "image";
    std::string outName = s1 + s2;

    imshow("original", input);
    imshow("Our", our_edges);
    imshow("OpenCV", cv_edges);
    waitKey();

    return 0;
}
