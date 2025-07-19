#include <iostream>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include <print>  

float w = 250.0f; // Width of the destination image
float h = 350.0f; // Height of the destination image

using namespace cv;
using namespace std;

//How to warp images 
#if 1  
int main()
{
	// Load the image from file
	std::string path = "resources/test.jpg";
	Mat img = imread(path); // Load the image from the specified path
	
	Point2f srcPoints[4] = { {550,79},{856,148}, {752,532}, {444,462} };
	Point2f dstPoints[4] = { {0,0}, {w,0}, {w,h}, {0,h} }; // Define the destination points for the perspective warp

	// Create a transformation matrix using the source and destination points
	Mat matrix = getPerspectiveTransform(srcPoints, dstPoints);
	// Apply the perspective warp to the image using the transformation matrix
	Mat imgWarped;	
	warpPerspective(img, imgWarped, matrix, Point(w,h));

	for (int i = 0; i < 4; i++)
	{
		circle(img, srcPoints[i], 10, Scalar(0, 0, 255), FILLED); // Draw circles on the source points
		//circle(imgWarped, dstPoints[i], 10, Scalar(0, 0, 255), FILLED); // Draw circles on the destination points
	}
	
	imshow("Image", img);
	imshow("Warped Image", imgWarped); // Display the warped image
	waitKey(0); // Wait indefinitely until a key is pressed  
}
#endif  
// Basic Functions