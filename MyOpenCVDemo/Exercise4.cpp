#include "pch.h"
#include "Exercise4.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

const int display_height = 500;
const int display_weight = 500;
vector<cv::Mat1b> numbers;

void init_numbers()
{
	//init numbers
	for (int i = 0; i < 11; i++)
		numbers.push_back(cv::Mat1b::zeros(20, 10));
	//0:
	for (int i = 2; i < 8; i++)
	{
		numbers[0].at<unsigned char>(2, i) = 255;
		numbers[0].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 17; i++)
	{
		numbers[0].at<unsigned char>(i, 2) = 255;
		numbers[0].at<unsigned char>(i, 7) = 255;
	}
	//1:
	for (int i = 2; i < 8; i++)
	{
		numbers[1].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 17; i++)
	{
		numbers[1].at<unsigned char>(i, 5) = 255;
	}
	numbers[1].at<unsigned char>(5, 2) = 255;
	numbers[1].at<unsigned char>(4, 3) = 255;
	numbers[1].at<unsigned char>(3, 4) = 255;
	numbers[1].at<unsigned char>(2, 5) = 255;
	//2:
	for (int i = 2; i < 8; i++)
	{
		numbers[2].at<unsigned char>(2, i) = 255;
		numbers[2].at<unsigned char>(9, i) = 255;
		numbers[2].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 9; i++)
	{
		numbers[2].at<unsigned char>(i, 7) = 255;
	}
	for (int i = 10; i < 17; i++)
	{
		numbers[2].at<unsigned char>(i, 2) = 255;
	}
	//3:
	for (int i = 2; i < 8; i++)
	{
		numbers[3].at<unsigned char>(2, i) = 255;
		numbers[3].at<unsigned char>(9, i) = 255;
		numbers[3].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 9; i++)
	{
		numbers[3].at<unsigned char>(i, 7) = 255;
	}
	for (int i = 10; i < 17; i++)
	{
		numbers[3].at<unsigned char>(i, 7) = 255;
	}
	//4:
	for (int i = 2; i < 8; i++)
	{
		numbers[4].at<unsigned char>(10, i) = 255;
	}
	for (int i = 2; i < 18; i++)
	{
		numbers[4].at<unsigned char>(i, 5) = 255;
	}
	numbers[4].at<unsigned char>(4, 4) = 255;
	numbers[4].at<unsigned char>(5, 4) = 255;
	numbers[4].at<unsigned char>(6, 3) = 255;
	numbers[4].at<unsigned char>(7, 3) = 255;
	numbers[4].at<unsigned char>(8, 3) = 255;
	numbers[4].at<unsigned char>(9, 2) = 255;
	numbers[4].at<unsigned char>(10, 2) = 255;
	//5:
	for (int i = 2; i < 8; i++)
	{
		numbers[5].at<unsigned char>(2, i) = 255;
		numbers[5].at<unsigned char>(9, i) = 255;
		numbers[5].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 9; i++)
	{
		numbers[5].at<unsigned char>(i, 2) = 255;
	}
	for (int i = 10; i < 17; i++)
	{
		numbers[5].at<unsigned char>(i, 7) = 255;
	}
	//6:
	for (int i = 2; i < 8; i++)
	{
		numbers[6].at<unsigned char>(2, i) = 255;
		numbers[6].at<unsigned char>(9, i) = 255;
		numbers[6].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 17; i++)
	{
		numbers[6].at<unsigned char>(i, 2) = 255;
	}
	for (int i = 10; i < 17; i++)
	{
		numbers[6].at<unsigned char>(i, 7) = 255;
	}
	//7:
	for (int i = 2; i < 8; i++)
	{
		numbers[7].at<unsigned char>(2, i) = 255;
	}
	for (int i = 3; i < 6; i++)
	{
		numbers[7].at<unsigned char>(i, 7) = 255;
	}
	for (int i = 6; i < 10; i++)
	{
		numbers[7].at<unsigned char>(i, 6) = 255;
	}
	for (int i = 10; i < 14; i++)
	{
		numbers[7].at<unsigned char>(i, 5) = 255;
	}
	for (int i = 14; i < 18; i++)
	{
		numbers[7].at<unsigned char>(i, 4) = 255;
	}
	//8:
	for (int i = 2; i < 8; i++)
	{
		numbers[8].at<unsigned char>(2, i) = 255;
		numbers[8].at<unsigned char>(9, i) = 255;
		numbers[8].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 17; i++)
	{
		numbers[8].at<unsigned char>(i, 2) = 255;
	}
	for (int i = 3; i < 17; i++)
	{
		numbers[8].at<unsigned char>(i, 7) = 255;
	}
	//9:
	for (int i = 2; i < 8; i++)
	{
		numbers[9].at<unsigned char>(2, i) = 255;
		numbers[9].at<unsigned char>(9, i) = 255;
		numbers[9].at<unsigned char>(17, i) = 255;
	}
	for (int i = 3; i < 17; i++)
	{
		numbers[9].at<unsigned char>(i, 7) = 255;
	}
	for (int i = 3; i < 10; i++)
	{
		numbers[9].at<unsigned char>(i, 2) = 255;
	}
}

void help()
{
	cout << "Please Input numbeer'0'-'9', and other keys will quit" << endl;
}

void test1() {
	//init numbers and display
	init_numbers();
	help();
	cv::Mat1b display = cv::Mat1b::zeros(display_height, display_weight);
	unsigned count = 0;
	unsigned hang = 0;
	unsigned lie = 0;

	//show the empty image
	cv::namedWindow("Typewriter", cv::WINDOW_AUTOSIZE);
	cv::imshow("Typewriter", display);

	//loop for input
	int c = cv::waitKey(0);
	do
	{
		if ((char)c == 13)
		{
			hang++;
			lie = 0;
		}
		else if ((char)c == 8)
		{
			count--;
			int tmp = lie;
			if (tmp > 0)
				lie--;
			else if (tmp == 0)
			{
				hang--;
				lie = 24;
			}
			cout << "hang:" << hang << "lie:" << lie << endl;
			numbers[10].copyTo(display.rowRange(0 + 20 * hang, 20 + 20 * hang).colRange(0 + 10 * lie, 10 + 10 * lie));
		}
		else
		{
			cout << "number input" << endl;
			numbers[c - '0'].copyTo(display.rowRange(0 + 20 * hang, 20 + 20 * hang).colRange(0 + 10 * lie, 10 + 10 * lie));
			count++;
			lie++;
		}
		cout << (char)c << endl;
		cv::imshow("Typewriter", display);
		c = cv::waitKey(0);
	} while (true);

	cv::waitKey(0);
}

void test2a()
{
	cv::Mat1b int_image(200, 100);
	cv::Mat1f float_image(200, 100);
	cv::RNG rng(12345);
	//对uchar1类型的Mat填充0-255的随机值
	rng.fill(int_image, cv::RNG::UNIFORM, 0, 255);
	//对float1类型的Mat赋值0
	float_image = 0;
	cv::namedWindow("int_image", cv::WINDOW_AUTOSIZE);
	cv::imshow("int_image", int_image);
	//在3.4.5中可以imshow单通道浮点，在4.0.0中不可以imshow单通道浮点
	cv::namedWindow("float_image", cv::WINDOW_AUTOSIZE);
	cv::imshow("float_image", float_image);
	cv::waitKey(0);
}


void test2b()
{
	cv::Mat1b int_image(200, 100);
	cv::Mat1f float_image(200, 100);
	cv::RNG rng(12345);
	//对uchar1类型的Mat填充0-255的随机值
	rng.fill(int_image, cv::RNG::UNIFORM, 0, 255);
	//对float1类型的Mat赋值0
	float_image = 0;
	cv::namedWindow("int_image", cv::WINDOW_AUTOSIZE);
	cv::imshow("int_image", int_image);

	//对于单通道浮点的Mat计算积分图
	for (int i = 0; i < 199; i++)
	{
		for (int j = 0; j < 99; j++)
		{
			float_image.at<float>(i, j) = cv::sum(float_image.rowRange(0, i + 1).colRange(0, j + 1))[0];
		}
	}
	float_image /= float_image.at<float>(199, 99);

	//在3.4.5中可以imshow单通道浮点，在4.0.0中不可以imshow单通道浮点
	cv::namedWindow("float_image", cv::WINDOW_AUTOSIZE);
	cv::imshow("float_image", float_image);
	cv::waitKey(0);
}

void Exercise4::ExerciseMain()
{
	//test1();
	//test2a();
	test2b();
}

