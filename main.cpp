#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
//#include <opencv2/gpu/gpu.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
    // argv[1] - whaere the image is located
    char* imagePath = argv[1];

    // create a MAT object for input image
    Mat image;
    Mat output;
    // load an image
    image = imread( imagePath, 1 );

    if( argc != 2 || !image.data )
    {
        printf( " No image data \n " );
        return -1;
    }

    // create a MAT object for gray image
    cuda::GpuMat input_gpu_image, output_gpu_image;

    input_gpu_image.upload(image);
    // convert to Greyscale format
    //cvtColor( image, gray_image, CV_BGR2GRAY );
    cuda::cvtColor( input_gpu_image, output_gpu_image, COLOR_BGR2GRAY );

//    cout << to_string(gray_image<cv::Vec3b>(0,0)) << endl;
    // save the transformed image to a file
    //imwrite( "../images/GrayImage.jpg", gray_image );

    output_gpu_image.download(output);
    imwrite("../images/GrayImage.jpg", output);
    // creates two windows
    namedWindow( imagePath, CV_WINDOW_AUTOSIZE );
    namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

    // imshow() displays an image in the specified window. 
    // If the window was created with the CV_WINDOW_AUTOSIZE flag, 
    // the image is shown with its original size
    imshow( imagePath, image );
    imshow( "Gray image", output );

    // wait for key press
    waitKey(0);

    return 0;
}

