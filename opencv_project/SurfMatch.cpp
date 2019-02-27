#include "pch.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<iostream>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int dist_large = 5;  //该参数决定寻找到的特征点对，参数越大，匹配的特征点对数目越多，但特征点对的精确性下降

int SurfMatch(Mat srcImg1, Mat srcImg2, double Nx[], double Ny[], double N_3x[], double N_3y[], int num) {
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
	FlannBasedMatcher  matcher;
	vector <DMatch> matches;

	vector <KeyPoint> keypoints1, keypoints2;
	Mat dstImg1, dstImg2;
	int minHessian = 100;
	Ptr<SurfFeatureDetector> detector = SurfFeatureDetector::create(minHessian);
	detector->detectAndCompute(srcImg1, Mat(), keypoints1, dstImg1);
	detector->detectAndCompute(srcImg2, Mat(), keypoints2, dstImg2);

	Mat imgKeypoints1, imgKeypoints2;
	drawKeypoints(srcImg1, keypoints1, imgKeypoints1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcImg2, keypoints2, imgKeypoints2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	
	matcher.match(dstImg1, dstImg2, matches);
	double Max_dist = 0;
	double Min_dist = 100;
	for (int i = 0; i < dstImg1.rows; i++){
		double dist = matches[i].distance;
		if (dist < Min_dist)
			Min_dist = dist;
		if (dist > Max_dist)
			Max_dist = dist;
	}
	//cout << "最短距离" << Min_dist << endl;
	//cout << "最长距离" << Max_dist << endl;
	vector<DMatch>goodmaches;
	for (int i = 0; i < dstImg1.rows && num <= 100000; i++){
		if (matches[i].distance < dist_large * Min_dist && matches[i].distance < Max_dist / 3) {
            goodmaches.push_back(matches[i]);
		    int square1 = matches[i].queryIdx;
			int square2 = matches[i].trainIdx;
			Nx[num] = keypoints1[square1].pt.x;
			Ny[num] = keypoints1[square1].pt.y;
			N_3x[num] = keypoints2[square2].pt.x;
			N_3y[num++] = keypoints2[square2].pt.y;
			//cout << keypoints1[square1].pt.x << " " << keypoints1[square1].pt.y << " " << keypoints2[square2].pt.x << " " << keypoints2[square2].pt.y << endl;
		}
	}
#ifdef __TEST
	Mat imgMaches;
	drawMatches(srcImg1, keypoints1, srcImg2, keypoints2, goodmaches, imgMaches);
	//drawMatches(srcImg2, keypoints2, srcImg1, keypoints1, goodmaches, imgMaches);
	//for (int i = 0; i < goodmaches.size(); i++)
	//{
//		cout << "符合条件的匹配：" << goodmaches[i].queryIdx << "--" << goodmaches[i].trainIdx << endl;
	//}
	//imshow("原图1", srcImg1);
	//imshow("原图2", srcImg2);

	imshow("匹配效果", imgMaches);
#endif // __TEST
	//imwrite("E:\\imgMatches.jpg", imgMaches);
	//waitKey(0);
	return num;
}