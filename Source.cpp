#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv; 
/*int main(int argc, char** argv)
{
	string filename = "fukuoka.avi"; 
	VideoCapture capture(filename);
	Mat frame;

	if (!capture.isOpened()){

		cout << "Error when reading steam_avi" << endl;;

	}
	namedWindow("w", 1);
	for (;;)
	{
		capture >> frame;
		if (frame.empty())
			break;
		imshow("w", frame);
		waitKey(20); // waits to display frame
	}
	waitKey(0); // key press to close window
	// releases and window destroy are automatic in C++ interface
}*/
/*
#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui_c.h>
//#include <opencv2/gpu/gpu.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std; 
int main(){
	Mat src = imread("car.jpg", 0);
	if (!src.data) exit(1);

	cout << "Dd" << endl;
	cuda::GpuMat d_src(src);
	cuda::GpuMat d_dst; 
	cuda::bilateralFilter(d_src, d_dst, 15, 80, 80);

	Mat dst(d_dst);
	imwrite("out.png", dst);
	return 0;
}*/

int main(int argc, char** argv)
{
	// argv[1] - whaere the image is located 

	// create a MAT object for input image
	Mat image;
	Mat output;
	// load an image
	image = imread("car.jpg", 1);

	if (!image.data)
	{
		printf(" No image data \n ");
		return -1;
	}

	// create a MAT object for gray image
	cuda::GpuMat input_gpu_image, output_gpu_image;

	input_gpu_image.upload(image);
	// convert to Greyscale format
	//cvtColor( image, gray_image, CV_BGR2GRAY );
	cuda::cvtColor(input_gpu_image, output_gpu_image, COLOR_BGR2GRAY);

	//    cout << to_string(gray_image<cv::Vec3b>(0,0)) << endl;
	// save the transformed image to a file
	//imwrite( "../images/GrayImage.jpg", gray_image );

	output_gpu_image.download(output);
	imwrite("../images/GrayImage.jpg", output);
	// creates two windows
	namedWindow("car.jpg", CV_WINDOW_AUTOSIZE);
	namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

	// imshow() displays an image in the specified window. 
	// If the window was created with the CV_WINDOW_AUTOSIZE flag, 
	// the image is shown with its original size
	imshow("car.jpg", image);
	imshow("Gray image", output);

	// wait for key press
	waitKey(0);

	return 0;
}

