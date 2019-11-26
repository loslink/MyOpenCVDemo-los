#include "pch.h"
#include "DetectFace.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

#define CASCADENAME			"./DetectFace/haarcascade_frontalface_alt2.xml"
#define NESTEDCASCADENAME	"./DetectFace/haarcascade_eye_tree_eyeglasses.xml"
#define FACEPHOTO_FACENAME  "./DetectFace/result.jpg"
#define DETECT_IMAGE		"./DetectFace/test.jpg"



void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade, double scale, bool tryflip)
{
	double t = 0;
	vector<Rect> faces, faces2;
	/* 定义七种颜色用于人脸标记 */
	const static Scalar colors[] =
	{
		Scalar(255,0,0),
		Scalar(255,128,0),
		Scalar(255,255,0),
		Scalar(0,255,0),
		Scalar(0,128,255),
		Scalar(0,255,255),
		Scalar(0,0,255),
		Scalar(255,0,255)
	};

	Mat gray, smallImg;

	/* 因为用的是类haar特征，所以都是基于灰度图像的，这里要转换成灰度图像 */
	cvtColor(img, gray, COLOR_BGR2GRAY);

	/* 将图片缩小，加快检测速度 */
	double fx = 1 / scale;
	/* 将尺寸缩小到1/scale, 用线性插值 */
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	/* 直方图均衡 */
	equalizeHist(smallImg, smallImg);

	/* 用来计算算法执行时间 */
	t = (double)getTickCount();

	/*人脸检测
		smallImg：输入的原图
		faces	：表示检测到的人脸目标序列
		1.1		：每次图像尺寸减小的比例为1.1
		2		：每一个目标至少要被检测到3次才算是真的目标
		CV_HAAR_SCALE_IMAGE：表示不是缩放分类器来检测，而是缩放图像
		Size(30, 30) 目标的最大最小尺寸
	*/
	cascade.detectMultiScale(smallImg, faces, 1.1, 4, CASCADE_SCALE_IMAGE, Size(30, 30));
	if (tryflip)
	{
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r)
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}

	/* 相减为算法执行的时间 */
	t = (double)getTickCount() - t;
	printf("detection time = %g ms\n", t * 1000 / getTickFrequency());

	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		/* 人脸长宽比例，在0.75-1.3 间画圆，其他范围画矩形 */
		double aspect_ratio = (double)r.width / r.height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			/*还原原来尺寸 计算圆心和圆半径 */
			center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);
			radius = cvRound((r.width + r.height)*0.25*scale);
			/* 画出人脸检测区域 画圆 */
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
		{
			/* 画出检测区域，画矩形 */
			rectangle(img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
				Point(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)), color, 3, 8, 0);
		}

		/* 检测到人眼，在人脸上画出人眼 */
		if (nestedCascade.empty())
		{
			continue;
		}

		smallImgROI = smallImg(r);

		/* 人眼检测 */
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2, CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t j = 0; j < nestedObjects.size(); j++)
		{
			Rect nr = nestedObjects[j];
			/*还原原来尺寸 计算圆心和圆半径 */
			center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
			center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
			radius = cvRound((nr.width + nr.height)*0.25*scale);
			/* 画出人眼检测区域 画圆*/
			circle(img, center, radius, color, 3, 8, 0);
		}
	}
	/* 显示图像 img */
	imshow("result", img);
}


int DetectFace::detectFace()
{
	Mat frame, image;
	bool tryflip = false;
	CascadeClassifier cascade, nestedCascade;
	double scale = 1.3;

	/* 加载分类器 */
	if (!nestedCascade.load(NESTEDCASCADENAME))
	{
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
	}
	if (!cascade.load(CASCADENAME))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return -1;
	}

	/* 加载图片 */
	image = imread(DETECT_IMAGE, 1);
	if (image.empty())
	{
		cout << "Couldn't read iamge" << DETECT_IMAGE << endl;

	}

	cout << "Detecting face(s) in " << DETECT_IMAGE << endl;

	/* 检测人脸及眼睛并画出检测到的区域 */
	if (!image.empty())
	{
		detectAndDraw(image, cascade, nestedCascade, scale, tryflip);
		waitKey(0);
	}
}


DetectFace::DetectFace()
{
}


DetectFace::~DetectFace()
{
}
