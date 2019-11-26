// MyOpenCVDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "AgeGender/AgeGender.h"
#include "DetectFace/DetectFace.h"

int main()
{
	//年龄检测
	//ageGender();

	//脸部检测
	DetectFace detect = DetectFace();
	detect.detectFace();

	return 0;
}

