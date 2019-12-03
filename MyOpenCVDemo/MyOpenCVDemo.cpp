// MyOpenCVDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "AgeGender/AgeGender.h"
#include "DetectFace/DetectFace.h"
#include "OpenCVTest.h"
#include "Exercise.h"
#include "Exercise4.h"
#include "Exercise5.h"

int main()
{
	//年龄检测
	//ageGender();

	//脸部检测
	/*DetectFace detect = DetectFace();
	detect.detectFace();*/

	//OpenCVTest().playVideo();

	//OpenCVTest().videoToLogPolar();

	//Exercise4().ExerciseMain();

	//OpenCVTest().alphaBlendImage();

	Exercise5().ExerciseMain();

	return 0;
}

