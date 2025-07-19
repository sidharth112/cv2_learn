#include <iostream>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include <print>  

using namespace cv;
using namespace std;

//How to warp images 
#if 1  
int main()
{
	//Blank image  
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); // Corrected CV_8U3 to CV_8UC3
	Rect roi(100, 100, 300, 300); // Define a region of interest (ROI)

	putText(img, "Sidharth", Point(200, 200), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 0, 0), 2); // Write text on the image
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 0, 0), 5); // Draw a blue diagonal line
	rectangle(img, roi, Scalar(0, 69, 255), 2); // Draw a filled rectangle in the ROI
	// Corrected the circle function call by adding the missing thickness parameter
	//circle(img, Point(256, 256), 100, Scalar(0, 69, 255), FILLED);  
	imshow("Image", img);
	waitKey(0); // Wait indefinitely until a key is pressed  
}
#endif  
// Basic Functions