#include "pch.h"
#include "Exercise5.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void test1a() {

	cv::Mat bgMat;
	bgMat = cv::Mat3b::zeros(100, 100);

	/*cv::Mat m(100, 100, CV_8UC3);
	m = 0;*/

	cv::circle(bgMat, cv::Point(50, 50), 20, cv::Scalar(255.0, 0.0, 0.0), 1);

	cv::namedWindow("win1", cv::WINDOW_AUTOSIZE);
	cv::imshow("win1", bgMat);

	cv::waitKey(0);
}

void test2() {

	cv::Mat bgMat;
	bgMat = cv::Mat3b::zeros(100,100);

	cv::rectangle(bgMat,cv::Point(20,5),cv::Point(40,20),cv::Scalar(0,255,0),cv::FILLED);

	cv::namedWindow("win1", cv::WINDOW_AUTOSIZE);
	cv::imshow("win1", bgMat);

	cv::waitKey(0);
}

void test3() {
	cv::Mat src = cv::Mat3b::zeros(100,100);
	int p1x = 20, p1y = 5;
	int p2x = 40, p2y = 20;

	for (int i = 0; i < src.rows; i++) {
	
		uchar* data = src.ptr<uchar>(i);//获取第i行的首地址
		//data += 10;//地址偏移
		for (int j = 0; j < src.cols;j++) {
			if (i >= p1y && i<= p2y && j>= p1x && j<= p2x) {
				
				*(data+ j * src.channels() + 1) = 255;//指针偏移，绿色通道重新赋值

				//src.at<cv::Vec3b>(i, j)[1] = 255;

				//src.ptr<cv::Vec3b>(i, j)->val[1] = 255;
			}
		}
		
	}
	cv::namedWindow("win1", cv::WINDOW_AUTOSIZE);
	cv::imshow("win1", src);
	cv::waitKey(0);
}

void test4() {
	cv::Mat m(210, 210, CV_8UC1);
	m = 0;
	for (int i = 1; i < 11; i++)
	{
		cv::Rect rest(10 * i, 10 * i, 210 - 20 * i, 210 - 20 * i);//定义一个框
		cv::Mat mask = m(rest);//这个tmp是个引用;roi区域
		mask.setTo((i + 1) * 20);//setTo能进行值的设置，
		//src.setTo(0,src < 10);这句话的意思是，当src中的某个像素值小于10的时候，就将该值设置成0.
	}
	cv::namedWindow("output", cv::WINDOW_AUTOSIZE);
	cv::imshow("output", m);

	/*Mat src(3, 3, CV_8UC1);
	src = 0;
	Mat mask2(3, 3, CV_8UC1, Scalar(0));
	//把矩阵mask(也是矩阵)中元素不为0的点全部变为value值；
	src.setTo(100, mask2);
	cout << src << endl;*/

	cv::waitKey(0);

}

void test5() {
	cv::Mat src;
	src = cv::imread("D:/VisualStudioWorkSpace/AgeGender/AgeGender/images/chil.jpg");
	cv::Rect rect1(50, 100, 200, 300);
	cv::Rect rect2(200, 60, 200, 300);
	cv::Mat tmp1 = src(rect1);
	cv::Mat tmp2 = src(rect2);
	cv::bitwise_not(tmp1, tmp1);
	cv::bitwise_not(tmp2, tmp2);
	cv::namedWindow("output",cv::WINDOW_AUTOSIZE);
	cv::imshow("output", src);
	cv::waitKey(0);


}

void test6() {
	cv::Mat src;
	src = cv::imread("D:/VisualStudioWorkSpace/AgeGender/AgeGender/images/chil.jpg");
	vector<cv::Mat> b_g_r;
	cv::split(src, b_g_r);
	cv::imshow("input", src);
	//a.
	cv::imshow("b", b_g_r[0]);//opencv中，RGB三个通道是反过来的
	cv::imshow("g", b_g_r[1]);
	cv::imshow("r", b_g_r[2]);
	//b.
	cv::Mat clone1 = b_g_r[1].clone();
	cv::Mat clone2 = b_g_r[1].clone();
	//c.
	double maxNum, minNum;
	cv::minMaxLoc(b_g_r[1], &minNum, &maxNum);//传递引用获取值
	cout << "maxNum:" << maxNum << "   " << "minNum:" << minNum << endl;
	//d.
	uchar thresh = (uchar)(maxNum - minNum) / 2;
	clone1 = (uchar)(thresh);
	cv::imshow("clone1:", clone1);
	//e.
	clone2 = 0;
	cv::compare(b_g_r[1], clone1, clone2, cv::CMP_GE);//匹配则255，否则0；CMP_GE：greater equal
	cv::imshow("clone2:", clone2);
	//f.
	cv::subtract(b_g_r[1], thresh / 2, b_g_r[1], clone2);
	cv::imshow("substract:", clone2);
	cv::waitKey(0);
}

void testMat()
{
	Mat img(5, 3, CV_8UC3, Scalar(50, 50, 50));
	cout << "rows:" << img.rows << endl;
	cout << "cols:" << img.cols << endl;
	cout << "channels:" << img.channels() << endl;
	cout << "dims:" << img.dims << endl;

	// 每个元素大小，单位字节
	cout << "elemSize:" << img.elemSize() << endl;    //1 * 3,一个位置，三个通道的CV_8U  
	// 每个通道大小，单位字节
	cout << "elemSize1:" << img.elemSize1() << endl;   //1 

	/*
	每一行（第一级）在矩阵内存中，占据的字节的数量
	二维图像由一行一行（第一级）构成，而每一行又由一个一个点（第二级）构成
	二维图像中step[0]就是每一行（第一级）在矩阵内存中，占据的字节的数量。
	也就是说step[i]就是第i+1级在矩阵内存中占据的字节的数量。
	*/
	cout << "step[0]:" << img.step[0] << endl;   //3 * ( 1 * 3 )  
	cout << "step[1]:" << img.step[1] << endl;   //1 * 3  
	cout << "total:" << img.total() << endl;   //3*5  

	//----------------------地址运算---------------------//
	for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			//[row,col]像素的第1通道地址解析为Blue通道
			*(img.data + img.step[0] * row + img.step[1] * col) += 15;

			//[row,col]像素的第2通道地址解析为Green通道
			*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1()) += 16;

			//[row,col]像素的第3通道地址解析为Red通道
			*(img.data + img.step[0] * row + img.step[1] * col + img.elemSize1() * 2) += 17;

		}
	}
	cout << "地址运算:\n" << img << endl;

	//----------------------Mat的成员函数at<>()---------------------//
	for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			/*
			.at  return (img.data + step.p[0] * i0))[i1]
			直接给[row,col]赋值，但是访问速度较慢
			*/
			img.at<Vec3b>(row, col) = Vec3b(0, 1, 2);
		}
	}
	cout << "成员函数at<>():\n" << img << endl;

	//----------------------Mat的成员函数ptr<>()---------------------//
	int nr = img.rows;
	int nc = img.cols * img.channels();//每一行的元素个数
	for (int j = 0; j < nr; j++)
	{
		uchar* data = img.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			*data++ += 99;
		}
	}
	cout << "成员函数ptr<>():\n" << img << endl;
}



void Exercise5::ExerciseMain()
{
	test6();

}


