//this program is modified from http://coyagi.tistory.com/entry/c-OpenCV-%EC%82%AC%EC%A7%84%ED%9D%91%EB%B0%B1%EB%B3%80%ED%99%981
//Created by hojae Son 10/20/2016

#include <cuda.h>
#include <cuda_runtime.h>
#include<opencv2/opencv.hpp>  
#include "device_launch_parameters.h" 
#include <iostream>

using namespace cv;
using namespace std;

void toGrayScale(IplImage* frame);

void main()
{ 
	CvCapture* capture = cvCreateFileCapture("C:\\Users\\pancake\\Desktop\\test.avi"); // VIDEO PATH FROM LOCAL

	IplImage* frame;
	char c; 
	while (1){
		frame = cvQueryFrame(capture);
		if (!frame) break;  
		toGrayScale(frame); //ACTUAL FUNCTION
		c = cvWaitKey(33);
		if (c == 27) break;
	} 
	  
	cvWaitKey(0);
	cvReleaseImage(&frame); 
}

void toGrayScale(IplImage* frame){ 
	//original video
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvShowImage("Original", frame);

	//grayScale video processing
	int  intensity; 
	uchar* data, *grayScale_data; 
	data = (uchar*)frame->imageData;

	frame = frame;  
	grayScale_data = (uchar*)frame->imageData;

	for (int i = 0; i < frame->height; i++)
		for (int j = 0; j < frame->width; j++)
		{
			intensity = (int)(0.114 * data[i* frame->width*frame->nChannels + j*frame->nChannels + 0]
				+ 0.587 * data[i* frame->width*frame->nChannels + j*frame->nChannels + 1]
				+ 0.299 * data[i* frame->width*frame->nChannels + j*frame->nChannels + 2]);
			for (int k = 0; k < frame->nChannels; k++)
				grayScale_data[i* frame->width*frame->nChannels + j*frame->nChannels + k] = intensity;
		}

	for (int i = 0; i < 1000; i += 100)
		for (int k = 0; k < 3; k++)
			printf("imageData[%3d] = %d \t frameData[%3d] = %d\n", i + k, data[i + k], i + k, grayScale_data[i + k]);

	cvNamedWindow("GrayScale", CV_WINDOW_AUTOSIZE);
	cvShowImage("GrayScale", frame); 
}

 