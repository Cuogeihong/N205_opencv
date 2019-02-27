#pragma once
#ifndef __RANSAC_H__
#define __RANSAC_H__

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

bool ransac(int num, double Nx[], double Ny[], double Nx_3[], double Ny_3[], double Matrix[][3]);

#endif 