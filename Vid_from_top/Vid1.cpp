
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/core.hpp"
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture file("D:/Progs/Birdeye/Resources/mv.mp4");
    UMat img, imgWarp;
    Mat matrix;
   
    int hmin = -1000, smin = 1, vmin = -1000;
   
    namedWindow("adjustment", (640,200));
    createTrackbar("Persp_Crop", "adjustment", &smin, 5);
    createTrackbar("Persp_Bottom", "adjustment", &vmin, 1000);
    createTrackbar("Persp_Top", "adjustment", &hmin, 1000);
    namedWindow("ForvardCam", 1);
    
    bool finish = false;
    while (!finish) {
       file >> img;
       float w = 1280, h = 720;
       Point2f src[4] = { {0,0},{w - 1,0},{0,h - 1},{w - 1,h - 1} };
       Point2f dst[4] = { {0.0f+ (float)hmin,0.0f- (float)smin *w},{w- (float)hmin,0.0f- (float)smin *w},{(float)vmin,h},{w- (float)vmin,h} };
       matrix = getPerspectiveTransform(src, dst);
       warpPerspective(img, imgWarp, matrix, Point(w, h));
       imshow("ForvardCam", imgWarp);
       if (waitKey(20) == 27) finish = true;
    }
    return 0;
}

