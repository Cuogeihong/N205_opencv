#pragma once
#ifndef __TDCD_H__
#define __TDCD_H__

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int TimeDomainChangeDetection(Mat srcImg1, Mat srcImg2, double Matrix[][3]);

#endif 