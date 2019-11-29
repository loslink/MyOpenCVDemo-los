#include "pch.h"
#include "Exercise.h"
#include <time.h>
#include <iostream>
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

void randTest() {
	//RNG rng((unsigned)time(NULL));//用这种方式是系统时间作为种子初始化rng，产生随机数是变的。注意加头文件#include<time.h>
	////RNG &rng = theRNG();//这种方式产生的随机数是不变的

	//double x = rng.uniform((double)0, (double)255);//产生一个0-255之间的double型数，下面两个相同理解
	//float y = rng.uniform(0.f, 255.f);
	//int z = rng.uniform(0, 255);
	//cout << x << endl << y << endl << z << endl;

	/*
   c.产生一些随机数
   */
   //创建RNG对象，使用默认种子“-1”
	cv::RNG rng;
	//产生[0,1)范围内均匀分布的double类型数据。
	double N1d = rng.uniform(0., 1.);
	cout << "rng.uniform(0., 1.)" << N1d << endl;
	int N2 = rng.next();                    //返回下一个随机整数，即N1.next();
	cout << "rng.next()" << N2 << endl;
	//返回下一个指定类型的随机数
	int N2a = rng.operator uchar();         //返回下一个无符号字符数
	cout << "rng.operator uchar()" << N2a << endl;
	int N2b = rng.operator schar();         //返回下一个有符号字符数
	cout << "rng.operator schar()" << N2b << endl;
	int N2c = rng.operator ushort();        //返回下一个无符号短型
	cout << "rng.operator ushort()" << N2c << endl;
	int N2d = rng.operator short int();     //返回下一个短整型数
	cout << "rng.operator short int()" << N2d << endl;
	int N2e = rng.operator int();           //返回下一个整型数
	cout << "rng.operator int()" << N2e << endl;
	int N2f = rng.operator unsigned int();  //返回下一个无符号整型数
	cout << "rng.operator unsigned int()" << N2f << endl;
	int N2g = rng.operator float();         //返回下一个浮点数
	cout << "rng.operator float()" << N2g << endl;
	int N2h = rng.operator double();        //返回下一个double型数
	cout << "rng.operator double()" << N2h << endl;
	int N2i = rng.operator ()();            //和rng.next( )等价
	cout << "rng.operator ()()" << N2i << endl;
	int N2j = rng.operator ()(100);         //返回[0,100)范围内的随机数
	cout << "rng.operator ()(100)" << N2j << endl;

	/*
	d.生成一个浮点数cv::Point2f，把它转换成整型的cv::Point，(我是用的是opencv4.0.0,似乎没有Pointz)把cv::Pointz转换成cv::Point2f
	*/
	cv::Point2f p2f(1.f, 2.f);
	cout << "Point2f" << p2f << endl;
	cv::Point p(p2f);
	cout << "Point" << p << endl;


	/*
	a.用cv::Mat33f和cv::Vec3f对象，生成一个3x3的矩阵和3行的向量
	*/
	cv::Matx33f m33f;
	m33f = cv::Matx33f::randn(3, 3);
	cout << "使用Matx33f生成3x3的矩阵：\n" << m33f << endl;

	cv::Vec<int, 3> f(1.f, 2.f, 3.f);
	cout << "使用Vec3f生成3行的向量：\n" << f << endl;

	////将Mat33f对象和Vec3f对象相乘，没报错但是也没结果
	//cv::Mat result;
	//result = m33f * f;
	//cout << result << endl;


}

void test3c() {
	/*
		a.用cv::Mat<>和cv::Vec模板，对应生成一个3x3矩阵和3行的向量
		*/
	cv::Mat m(3, 3, CV_32FC1);
	cv::randu(m, -1.0f, 1.0f);
	cout << "矩阵m:\n" << m << endl;

	cv::Vec<int, 3> f(1.f, 2.f, 3.f);
	cout << "3行向量Vec3f:" << f << endl;
	cout << "向量的行数：" << f.rows << endl;
	cout << "向量的列数：" << f.cols << endl;

	//将Mat和Vec相乘出错
	/*cv::Vec3f result;
	result = m*f;
	cout << "3x3矩阵和3行向量的乘积：" << result << endl;*/


	//将Vec映射到Mat后还是出错
	/*cv::Mat tmp_f = cv::Mat(f);
	cout << "tmp_f:" << tmp_f << endl;*/
	cv::Mat tmp_f = cv::Mat::ones(3,1, CV_32FC1);
	cout << "tmp_f:" << tmp_f << endl;
	cv::Mat result;
	result = m * tmp_f;
	cout << "3x3矩阵和3行向量的乘积：" << result << endl;
}


void Exercise::ExerciseMain()
{
	randTest();

	int ab = abs(-22);
	cout << ab << endl;

	/*
	a.选择一个负的浮点数
	b.计算它的绝对值，近似，向上取整，向下取整
	*/
	//生成一个负的浮点数
	Cv32suf f;
	f.f = -2.3;
	cout << "负的浮点数" << f.f << endl;

	/*
	cvRound()：返回跟参数最接近的整数值，即四舍五入；
	cvFloor()  ：返回不大于参数的最大整数值，即向下取整；
	cvCeil()：返回不小于参数的最小整数值，即向上取整；
    */
	cout << "cvRound(2.5) : " << cvRound(2.5) << endl;
	cout << "cvFloor(2.5) : " << cvFloor(2.5) << endl;
	cout << "cvCeil(2.5)  : " << cvCeil(2.5) << endl;

	test3c();


	

}

