/*
 *调用函数 int TimeDomainChangeDetection(Mat srcImg1, Mat srcImg2, double Matrix[][3]); 
 *srcImg1为前第N帧，srcImg2为当前帧
 *Matrix矩阵为变换参数矩阵
 * [ a1, b1, c1 ]
 * [ a2, b2, c2 ]
 * [ 0,  0,  1  ]
 *假设前第N帧图像中某个像素点坐标为(x,y)，当前帧中该像素点的坐标记为(x_3, y_3)
 *  [ x_3 ] = [ a1, b1, c1 ][ x ]
 *则[ y_3 ] = [ a2, b2, c2 ][ y ]
 *  [  1  ] = [ 0,  0,  1  ][ 1 ]  
 *可于"pch.h"文件中加入__TEST宏定义，运行后可见匹配图片以及所得变换参数矩阵以及变换参数矩阵对特征点的匹配情况，匹配情况一般较差，暂时没有找到解决办法
 *所有参数：
 * dist_large(SurfMatch.cpp)
 * Thnum, Thmistake; t, T(ransac.cpp)
 *参数意义在相应.cpp文件注释中列出
 */

#include "pch.h"
#include "ransac.h"
#include "SurfMatch.h"
#include "TimeDomainChangeDetection.h"

int main()
{


	
	Mat srcImg1 = imread("E:\\3.png", 1);
	Mat srcImg2 = imread("E:\\4.png", 1); 

	//int num = 0;
	//vector <KeyPoint> keypoints1, keypoints2;
	//if (!surf(srcImg1, keypoints1)) {
	//	cout << "error!!!" << endl;
	//}
	//if (!surf(srcImg2, keypoints2)) {
	//	cout << "error!!!" << endl;
	//}
	//if (!SurfMatch(srcImg1, srcImg2, Nx, Ny, Nx_3, Ny_3, num)) {
	//	cout << "error!!!" << endl;
	//}
	double Matrix[3][3];
	memset(Matrix, 0, sizeof(Matrix));
	if (!TimeDomainChangeDetection(srcImg1, srcImg2, Matrix)) 
		cout << "error" << endl;
	//for (int i = 0; i < 3; i++) {
    //    for (int j = 0; j < 3; j++) {
	//		cout << Matrix[i][j] << " ";
	//	}
	//	cout << endl;
	//}	
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单 
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
