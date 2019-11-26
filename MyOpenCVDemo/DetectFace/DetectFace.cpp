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
	/* ����������ɫ����������� */
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

	/* ��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ�� */
	cvtColor(img, gray, COLOR_BGR2GRAY);

	/* ��ͼƬ��С���ӿ����ٶ� */
	double fx = 1 / scale;
	/* ���ߴ���С��1/scale, �����Բ�ֵ */
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	/* ֱ��ͼ���� */
	equalizeHist(smallImg, smallImg);

	/* ���������㷨ִ��ʱ�� */
	t = (double)getTickCount();

	/*�������
		smallImg�������ԭͼ
		faces	����ʾ��⵽������Ŀ������
		1.1		��ÿ��ͼ��ߴ��С�ı���Ϊ1.1
		2		��ÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��
		CV_HAAR_SCALE_IMAGE����ʾ�������ŷ���������⣬��������ͼ��
		Size(30, 30) Ŀ��������С�ߴ�
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

	/* ���Ϊ�㷨ִ�е�ʱ�� */
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

		/* ���������������0.75-1.3 �仭Բ��������Χ������ */
		double aspect_ratio = (double)r.width / r.height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			/*��ԭԭ���ߴ� ����Բ�ĺ�Բ�뾶 */
			center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);
			radius = cvRound((r.width + r.height)*0.25*scale);
			/* ��������������� ��Բ */
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
		{
			/* ����������򣬻����� */
			rectangle(img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
				Point(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)), color, 3, 8, 0);
		}

		/* ��⵽���ۣ��������ϻ������� */
		if (nestedCascade.empty())
		{
			continue;
		}

		smallImgROI = smallImg(r);

		/* ���ۼ�� */
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2, CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t j = 0; j < nestedObjects.size(); j++)
		{
			Rect nr = nestedObjects[j];
			/*��ԭԭ���ߴ� ����Բ�ĺ�Բ�뾶 */
			center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
			center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
			radius = cvRound((nr.width + nr.height)*0.25*scale);
			/* �������ۼ������ ��Բ*/
			circle(img, center, radius, color, 3, 8, 0);
		}
	}
	/* ��ʾͼ�� img */
	imshow("result", img);
}


int DetectFace::detectFace()
{
	Mat frame, image;
	bool tryflip = false;
	CascadeClassifier cascade, nestedCascade;
	double scale = 1.3;

	/* ���ط����� */
	if (!nestedCascade.load(NESTEDCASCADENAME))
	{
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
	}
	if (!cascade.load(CASCADENAME))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return -1;
	}

	/* ����ͼƬ */
	image = imread(DETECT_IMAGE, 1);
	if (image.empty())
	{
		cout << "Couldn't read iamge" << DETECT_IMAGE << endl;

	}

	cout << "Detecting face(s) in " << DETECT_IMAGE << endl;

	/* ����������۾���������⵽������ */
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
