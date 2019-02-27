#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;
#pragma once
#ifndef __SURF_H__
#define __SURF_H__
bool surf(Mat, vector <KeyPoint> &);

#endif 