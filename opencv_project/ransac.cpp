#include "pch.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<cstdio>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

//int Thx = 100, Thy = 100;
int Thnum = 50, Thmistake = 3; //前一个参数用处不大，后一个参数决定对所尝试模型精确度的判断，数值越大判断越严格

bool ransac(int num, double Nx[], double Ny[], double Nx_3[], double Ny_3[], double Matrix[][3])  {
	srand((int)time(0));
	double t = 20000, T = 0.9993;  //这两个参数决定所得矩阵的精确性，t、T越大，精确性越大，但是修改后运行时间会显著增长，建议不要改动
	double sa1 = 0, sa2 = 0, sb1 = 0, sb2 = 0, sc1 = 0, sc2 = 0, ssum = 0;
	
	while (t > 1e-14) {
		int i, j, k;
		i = rand() % num;
		j = rand() % num;
		k = rand() % num;
		if (i >= j || i >= k || j >= k)
			continue;
		double x1, x2, x3, y1, y2, y3, x1_3, x2_3, x3_3, y1_3, y2_3, y3_3;
		x1 = Nx[i];
		x2 = Nx[j];
		x3 = Nx[k];
		y1 = Ny[i];
		y2 = Ny[j];
		y3 = Ny[k];
		x1_3 = Nx_3[i];
		x2_3 = Nx_3[j];
		x3_3 = Nx_3[k];
		y1_3 = Ny_3[i];
		y2_3 = Ny_3[j];
		y3_3 = Ny_3[k];
		double ta1, ta2, tb1, tb2, tc1, tc2, tsum = 0;

		tb1 = ((x1_3 - x2_3) * (x1 - x3) - (x1_3 - x3_3) * (x1 - x2)) / ((x1 - x3) * (y1 - y2) - (x1 - x2) * (y1 - y3));
		ta1 = (x1_3 - x2_3 - tb1 * (y1 - y2)) / (x1 - x2);
		tc1 = x1_3 - ta1 * x1 - tb1 * y1;
		tb2 = ((y2_3 - y1_3) * (x3 - x1) - (y3_3 - y1_3) * (x2 - x1)) / ((y2 - y1) * (x3 - x1) - (y3 - y1) * (x2 - x1));
		ta2 = (y2_3 - y1_3 - (y2 - y1) * tb2) / (x2 - x1);
		tc2 = y1_3 - ta2 * x1 - tb2 * y1;


		double tryx1_3 = ta1 * x1 + tb1 * y1 + tc1;
		double tryy1_3 = ta2 * x1 + tb2 * y1 + tc2;
		//printf("x : %lf, tx : %lf, y : %lf,ty : %lf", x1_3, tryx1_3, y1_3, tryy1_3);
		double mistake[100010], mistakeSum = 0;
		memset(mistake, 0, sizeof(mistake));
		for (int l = 0; l < num; l++) {
			double x = Nx[l], y = Ny[l], test_x_3, test_y_3, x_3 = Nx_3[l], y_3 = Ny_3[l];
			test_x_3 = ta1 * x + tb1 * y + tc1;
			test_y_3 = ta2 * x + tb2 * y + tc2;
			//printf("x_3 : %lf tx_3 : %lf y_3 : %lf, t_y_3 : %lf\n", x_3, test_x_3, y_3, test_y_3);
			mistake[l] = sqrt((test_x_3 - x_3)*(test_x_3 - x_3) + (test_y_3 - y_3)*(test_y_3 - y_3));
			mistakeSum += mistake[l];
			//if (abs(test_x_3 - x_3) < Thx && abs(test_y_3 - y_3) < Thy)
				//tsum += 1;
		}
		double mistakeAver = mistakeSum / num;
		for (int l = 0; l < num; l++)
			if (mistake[l] < mistakeAver / Thmistake) {
				tsum += 1;
				//						cout << "mistake_l: " << mistake[l] << "mistakeAver: " << mistakeAver << endl;
			}
		double delta = ssum - tsum;
		//cout << "num: " <<  num << "tsum: " << tsum << " ssum: " << ssum << endl;
		if (delta >= 0) {
			sa1 = ta1;
			sa2 = ta2;
			sb1 = tb1;
			sb2 = tb2;
			sc1 = tc1;
			sc2 = tc2;
			ssum = tsum;
		}	
		else if (exp(delta / t) * RAND_MAX > rand()){
			sa1 = ta1;
			sa2 = ta2;
			sb1 = tb1;
			sb2 = tb2;
			sc1 = tc1;
			sc2 = tc2;
			ssum = tsum;
		}
		t *= T;
	}
	/*
	 *此处不可删
	for (int i = 0; i < num; i++)
		for(int j = 0; j < num; j++)
			for (int k = 0; k < num; k++) {
				if (i >= j || i >= k || j >= k)
					continue;
				double x1, x2, x3, y1, y2, y3, x1_3, x2_3, x3_3, y1_3, y2_3, y3_3;
				x1 = Nx[i];
				x2 = Nx[j];
				x3 = Nx[k];
				y1 = Ny[i];
				y2 = Ny[j];
				y3 = Ny[k];
				x1_3 = Nx_3[i];
				x2_3 = Nx_3[j];
				x3_3 = Nx_3[k];
				y1_3 = Ny_3[i];
				y2_3 = Ny_3[j];
				y3_3 = Ny_3[k];
				double ta1, ta2, tb1, tb2, tc1, tc2, tsum = 0;
					
				tb1 = ((x1_3 - x2_3) * (x1 - x3) - (x1_3 - x3_3) * (x1 - x2)) / ((x1 - x3) * (y1 - y2) - (x1 - x2) * (y1 - y3));
				ta1 = (x1_3 - x2_3 - tb1 * (y1 - y2)) / (x1 - x2);
				tc1 = x1_3 - ta1 * x1 - tb1 * y1;
				tb2 = ((y2_3 - y1_3) * (x3 - x1) - (y3_3 - y1_3) * (x2 - x1)) / ((y2 - y1) * (x3 - x1) - (y3 - y1) * (x2 - x1));
				ta2 = (y2_3 - y1_3 - (y2 - y1) * tb2) / (x2 - x1);
				tc2 = y1_3 - ta2 * x1 - tb2 * y1;		
				
				
				double tryx1_3 = ta1 * x1 + tb1 * y1 + tc1;
				double tryy1_3 = ta2 * x1 + tb2 * y1 + tc2;
				//printf("x : %lf, tx : %lf, y : %lf,ty : %lf", x1_3, tryx1_3, y1_3, tryy1_3);
				double mistake[100010], mistakeSum = 0;
				memset(mistake, 0, sizeof(mistake));
				for (int l = 0; l < num; l++) {
					double x = Nx[l], y = Ny[l], test_x_3, test_y_3, x_3 = Nx_3[l], y_3 = Ny_3[l];
					test_x_3 = ta1 * x + tb1 * y + tc1;
                    test_y_3 = ta2 * x + tb2 * y + tc2;
					//printf("x_3 : %lf tx_3 : %lf y_3 : %lf, t_y_3 : %lf\n", x_3, test_x_3, y_3, test_y_3);
					mistake[l] = sqrt((test_x_3 - x_3)*(test_x_3 - x_3) + (test_y_3 - y_3)*(test_y_3 - y_3));
					mistakeSum += mistake[l];
					//if (abs(test_x_3 - x_3) < Thx && abs(test_y_3 - y_3) < Thy)
						//tsum += 1;
				}
				double mistakeAver = mistakeSum / num;
				for (int l = 0; l < num; l++)
					if (mistake[l] < mistakeAver / Thmistake) {
                        tsum += 1;
//						cout << "mistake_l: " << mistake[l] << "mistakeAver: " << mistakeAver << endl;
					}
						
				//cout << "num: " <<  num << "tsum: " << tsum << " ssum: " << ssum << endl;
				if (tsum > ssum) {
					sa1 = ta1;
					sa2 = ta2;
					sb1 = tb1;
					sb2 = tb2;
					sc1 = tc1;
					sc2 = tc2;
					ssum = tsum;
				}				
			} */
	if (ssum < num * 3/ 100) {
		cout << "警告：匹配极有可能出错，两帧之间差距相当大" << endl;
	}
#ifdef __TEST
	cout << "ssum: " << ssum << " num: " << num << " rate: " << (double)(ssum * 100 / num) << "%" << endl;
	if (ssum < num * Thnum / 100) {
		cout << "警告：匹配可能出错，两帧之间差距较大" << endl;
	}
#endif // __TEST
	Matrix[0][0] = sa1;
	Matrix[0][1] = sb1;
	Matrix[0][2] = sc1;
	Matrix[1][0] = sa2;
	Matrix[1][1] = sb2;
	Matrix[1][2] = sc2;
	Matrix[2][0] = 0;
	Matrix[2][1] = 0;
	Matrix[2][2] = 1;
	return 1;
}