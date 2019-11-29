#include "pch.h"
#include "OpenCVTest.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0;
cv::VideoCapture g_cap;
#define VIDEO_PATH "D:\\文件\\test.mp4"


void gaussianBlur( cv::Mat & image) {

	/*cv::namedWindow("win_in", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("win_out", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("win_out2", cv::WINDOW_AUTOSIZE);*/

	//cv::imshow("win_in", image);

	cv::Mat out;

	cv::GaussianBlur(image, out, cv::Size(51, 51), 3, 3);
	//cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);

	/*cv::imshow("win_out", out);

	cv::GaussianBlur(image, out, cv::Size(51, 51), 3, 3);
	cv::imshow("win_out2", out);*/

	//cv::waitKey(0);
	image = out;
}

void testPyrDown(cv::Mat & img1) {
	cv::Mat  img2;
	cv::namedWindow("win1",cv::WINDOW_AUTOSIZE);
	cv::namedWindow("win2",cv::WINDOW_AUTOSIZE);

	cv::imshow("win1",img1);

	cv::pyrDown(img1,img2);//降采样，宽高降为一半
	cv::imshow("win2",img2);

	cv::waitKey(0);
}

/*
边缘检测
*/
void testCanny(cv::Mat & img_rgb) {
	cv::Mat img_gry, img_cny;

	cv::namedWindow("win1",cv::WINDOW_AUTOSIZE);
	cv::namedWindow("win2",cv::WINDOW_AUTOSIZE);

	cv::cvtColor(img_rgb,img_gry,cv::COLOR_RGB2GRAY);
	cv::imshow("win1",img_gry);

	cv::Canny(img_gry,img_cny,10,100,3,true);
	cv::imshow("win2",img_cny);

	int x = 16, y = 32;
	cv::Vec3b px = img_rgb.at<cv::Vec3b>(x,y);//该位置像素的bgr值
	uchar blue = px[0];

	uchar g_px = img_gry.at<uchar>(y,x);//灰度图

	img_cny.at<uchar>(x, y) = 128;//改变该像素色值

	cv::waitKey(0);
}

void onTrackbarSlide(int pos,void *) {

	g_cap.set(cv::CAP_PROP_POS_FRAMES,pos);
	if (!g_dontset) {
		g_run = 1;
	}
	g_dontset = 0;
}

void OpenCVTest::playVideo() {

	cv::namedWindow("win1",cv::WINDOW_AUTOSIZE);
	g_cap.open(VIDEO_PATH);
	//g_cap.open(0);//打开第一个摄像头
	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int w = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int h = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	//cv::createTrackbar("Position","win1",&g_slider_position,frames,onTrackbarSlide);

	cv::Mat frame;
	for (;;) {
		if (g_run != 0) {
			g_cap >> frame;
			if (frame.empty()) break;
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;

			cv::setTrackbarPos("Position","win1",current_pos);
			//gaussianBlur(frame);
			//testPyrDown(frame);
			//testCanny(frame);
			cv::imshow("win1",frame);

			
			g_run -= 1;
		}

		char c = (char)cv::waitKey(10);
		if (c == 's') {
			g_run = 1;

		}
		if (c == 'r') {
			g_run = -1;
		}
		if (c == 27) {
			break;
		}
	}
}

/*
视频极对转换后保存到本地
*/
void OpenCVTest::videoToLogPolar() {
	cv::namedWindow("win",cv::WINDOW_AUTOSIZE);
	cv::namedWindow("logpolar",cv::WINDOW_AUTOSIZE);

	cv::VideoCapture cap(VIDEO_PATH);

	double fps = cap.get(cv::CAP_PROP_FPS);
	cv::Size size(
	    (int)cap.get(cv::CAP_PROP_FRAME_WIDTH),
		(int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)
	);

	cv::VideoWriter writer;
	writer.open("D:\\文件\\polar.mp4",cv::CAP_OPENCV_MJPEG,fps,size);

	cv::Mat polar_frame, bgr_frame;
	for (;;) {
		cap >> bgr_frame;
		if (bgr_frame.empty()) break;

		cv::imshow("win",bgr_frame);

		cv::logPolar(
		    bgr_frame,
			polar_frame,
			cv::Point2f(bgr_frame.cols/2,bgr_frame.rows/2),
			40,
			cv::WARP_FILL_OUTLIERS
		);

		cv::imshow("logpolar",polar_frame);
		writer << polar_frame;

		char c = cv::waitKey(10);
		if (c == 27) break;
	}
	cap.release();
}

/*
旋转图片
*/
void rotate(cv::Mat src, cv::Mat& dst, double angle)
{
	cv::Size src_sz = src.size();
	cv::Size dst_sz(src_sz.width, src_sz.height);

	cv::Point center = cv::Point(src.cols / 2, src.rows / 2);//旋转中心
	cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);//获得仿射变换矩阵

	cv::warpAffine(src, dst, rot_mat, dst_sz);
}


void OpenCVTest::alphaBlendImage() {
	string path1 = "D:\\VisualStudioWorkSpace\\MyOpenCVDemo\\MyOpenCVDemo\\AgeGender\\images\\chao1.jpg";
	string path2 = "D:\\VisualStudioWorkSpace\\MyOpenCVDemo\\MyOpenCVDemo\\AgeGender\\images\\chil.jpg";
	int x = 450, y = 480, w = 150, h = 150;
	double alpha = 0.4, beta = 0.6;

	cv::Mat src1 = cv::imread(path1,1);
	cv::Mat src2 = cv::imread(path2,1);

	rotate(src2, src2,-30.0);

	resize(src2, src2, cv::Size(w, h), (0, 0), (0, 0), 3);//缩小图片
	cv::Mat roi1(src1,cv::Rect(x,y,w,h));
	cv::Mat roi2(src2,cv::Rect(0,0,w,h));

	cv::addWeighted(roi1,alpha,roi2,beta,0.0,roi1);

	cv::namedWindow("Alpha Blend",cv::WINDOW_AUTOSIZE);
	cv::imshow("Alpha Blend",src1);

	cv::waitKey(0);
}

