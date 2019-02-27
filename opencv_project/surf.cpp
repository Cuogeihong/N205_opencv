#include "pch.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int minHessian = 100;


bool surf(Mat srcImg, vector <KeyPoint> &keypoints) {
	system("color 2F");

	imshow("srcImg", srcImg);
	
	Ptr<SURF> detector = SURF::create(minHessian);
	detector->detect(srcImg, keypoints);
	Mat imgKeypoints;
	drawKeypoints(srcImg, keypoints, imgKeypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("surfImg", imgKeypoints);
	waitKey(0);
	return 1;
}