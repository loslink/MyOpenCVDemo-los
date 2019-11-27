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
	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int w = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int h = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	cv::createTrackbar("Position","win1",&g_slider_position,frames,onTrackbarSlide);

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


