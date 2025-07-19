#include <iostream>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include <print>  

float w = 250.0f; // Width of the destination image
float h = 350.0f; // Height of the destination image

using namespace cv;
using namespace std;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 179, smax = 255, vmax = 255; // Define the HSV color range for detection
//How to Detect colors within an image
#if 1  
int main()
{
	// Load the image from file
	std::string path = "resources/pic.jpg";
	Mat img = imread(path); // Load the image from the specified path
	Mat imgHSV, mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV); // Convert the image from BGR to RGB color space


	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179); // Create a trackbar for minimum hue value
	createTrackbar("Hue Max", "Trackbars", &hmax, 179); // Create a trackbar for maximum hue value
	createTrackbar("Sat Min", "Trackbars", &smin, 255); // Create a trackbar for minimum saturation value
	createTrackbar("Sat Max", "Trackbars", &smax, 255); // Create a trackbar for maximum saturation value
	createTrackbar("Val Min", "Trackbars", &vmin, 255); // Create a trackbar for minimum value (brightness)
	createTrackbar("Val Max", "Trackbars", &vmax, 255); // Create a trackbar for maximum value (brightness)


	
while (true) {
	Scalar lower(hmin, smin, vmin); // Define the lower bound of the color range
	Scalar upper(hmax, smax, vmax); // Define the upper bound of the color range
	inRange(imgHSV, lower, upper, mask); // Threshold the HSV image to get only the colors in the specified range



	imshow("Image", img);
	imshow("Image HSV", imgHSV); // Display the original and HSV images
	imshow("Mask", mask); // Display the mask image showing the detected colors

	waitKey(1); // Wait indefinitely until a key is pressed  
	}
}
#endif  
// Basic Functions