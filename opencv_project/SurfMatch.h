#pragma once
#ifndef __SURFMATCH_H__
#define __SURFMATCH_H__

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int SurfMatch(Mat srcImg1, Mat srcImg2, double Nx[], double Ny[], double N_3x[], double N_3y[], int num);

#endif 