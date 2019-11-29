#include "pch.h"
#include "Exercise.h"
#include <time.h>
#include <iostream>
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

void randTest() {
	//RNG rng((unsigned)time(NULL));//�����ַ�ʽ��ϵͳʱ����Ϊ���ӳ�ʼ��rng������������Ǳ�ġ�ע���ͷ�ļ�#include<time.h>
	////RNG &rng = theRNG();//���ַ�ʽ������������ǲ����

	//double x = rng.uniform((double)0, (double)255);//����һ��0-255֮���double����������������ͬ���
	//float y = rng.uniform(0.f, 255.f);
	//int z = rng.uniform(0, 255);
	//cout << x << endl << y << endl << z << endl;

	/*
   c.����һЩ�����
   */
   //����RNG����ʹ��Ĭ�����ӡ�-1��
	cv::RNG rng;
	//����[0,1)��Χ�ھ��ȷֲ���double�������ݡ�
	double N1d = rng.uniform(0., 1.);
	cout << "rng.uniform(0., 1.)" << N1d << endl;
	int N2 = rng.next();                    //������һ�������������N1.next();
	cout << "rng.next()" << N2 << endl;
	//������һ��ָ�����͵������
	int N2a = rng.operator uchar();         //������һ���޷����ַ���
	cout << "rng.operator uchar()" << N2a << endl;
	int N2b = rng.operator schar();         //������һ���з����ַ���
	cout << "rng.operator schar()" << N2b << endl;
	int N2c = rng.operator ushort();        //������һ���޷��Ŷ���
	cout << "rng.operator ushort()" << N2c << endl;
	int N2d = rng.operator short int();     //������һ����������
	cout << "rng.operator short int()" << N2d << endl;
	int N2e = rng.operator int();           //������һ��������
	cout << "rng.operator int()" << N2e << endl;
	int N2f = rng.operator unsigned int();  //������һ���޷���������
	cout << "rng.operator unsigned int()" << N2f << endl;
	int N2g = rng.operator float();         //������һ��������
	cout << "rng.operator float()" << N2g << endl;
	int N2h = rng.operator double();        //������һ��double����
	cout << "rng.operator double()" << N2h << endl;
	int N2i = rng.operator ()();            //��rng.next( )�ȼ�
	cout << "rng.operator ()()" << N2i << endl;
	int N2j = rng.operator ()(100);         //����[0,100)��Χ�ڵ������
	cout << "rng.operator ()(100)" << N2j << endl;

	/*
	d.����һ��������cv::Point2f������ת�������͵�cv::Point��(�����õ���opencv4.0.0,�ƺ�û��Pointz)��cv::Pointzת����cv::Point2f
	*/
	cv::Point2f p2f(1.f, 2.f);
	cout << "Point2f" << p2f << endl;
	cv::Point p(p2f);
	cout << "Point" << p << endl;


	/*
	a.��cv::Mat33f��cv::Vec3f��������һ��3x3�ľ����3�е�����
	*/
	cv::Matx33f m33f;
	m33f = cv::Matx33f::randn(3, 3);
	cout << "ʹ��Matx33f����3x3�ľ���\n" << m33f << endl;

	cv::Vec<int, 3> f(1.f, 2.f, 3.f);
	cout << "ʹ��Vec3f����3�е�������\n" << f << endl;

	////��Mat33f�����Vec3f������ˣ�û������Ҳû���
	//cv::Mat result;
	//result = m33f * f;
	//cout << result << endl;


}

void test3c() {
	/*
		a.��cv::Mat<>��cv::Vecģ�壬��Ӧ����һ��3x3�����3�е�����
		*/
	cv::Mat m(3, 3, CV_32FC1);
	cv::randu(m, -1.0f, 1.0f);
	cout << "����m:\n" << m << endl;

	cv::Vec<int, 3> f(1.f, 2.f, 3.f);
	cout << "3������Vec3f:" << f << endl;
	cout << "������������" << f.rows << endl;
	cout << "������������" << f.cols << endl;

	//��Mat��Vec��˳���
	/*cv::Vec3f result;
	result = m*f;
	cout << "3x3�����3�������ĳ˻���" << result << endl;*/


	//��Vecӳ�䵽Mat���ǳ���
	/*cv::Mat tmp_f = cv::Mat(f);
	cout << "tmp_f:" << tmp_f << endl;*/
	cv::Mat tmp_f = cv::Mat::ones(3,1, CV_32FC1);
	cout << "tmp_f:" << tmp_f << endl;
	cv::Mat result;
	result = m * tmp_f;
	cout << "3x3�����3�������ĳ˻���" << result << endl;
}


void Exercise::ExerciseMain()
{
	randTest();

	int ab = abs(-22);
	cout << ab << endl;

	/*
	a.ѡ��һ�����ĸ�����
	b.�������ľ���ֵ�����ƣ�����ȡ��������ȡ��
	*/
	//����һ�����ĸ�����
	Cv32suf f;
	f.f = -2.3;
	cout << "���ĸ�����" << f.f << endl;

	/*
	cvRound()�����ظ�������ӽ�������ֵ�����������룻
	cvFloor()  �����ز����ڲ������������ֵ��������ȡ����
	cvCeil()�����ز�С�ڲ�������С����ֵ��������ȡ����
    */
	cout << "cvRound(2.5) : " << cvRound(2.5) << endl;
	cout << "cvFloor(2.5) : " << cvFloor(2.5) << endl;
	cout << "cvCeil(2.5)  : " << cvCeil(2.5) << endl;

	test3c();


	

}

