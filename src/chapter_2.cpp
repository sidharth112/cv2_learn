#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
using namespace std;

//Basic Functions
#if 1
int main()
{
	std::string imagePath = "resources/pic.jpg"; // Specify the path to your image file
	Mat image = imread(imagePath, IMREAD_COLOR); // Read the image file
	Mat ImageGrey, imgBlur, imgCanny, imgDil, imgErode;
	cvtColor(image, ImageGrey, COLOR_BGR2GRAY); // Convert the image to grayscale
	GaussianBlur(image, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 50, 150); // Apply Canny edge detection
	
	Point start(100, 100);
	Point end(400, 400);
	Scalar color(0,255,0);
	uint32_t thickness = 5;


	line(image, start, end, color, thickness);
	imshow("Image Line", image); // Display the image with a line drawn on it


	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // Create a rectangular structuring element
	dilate(imgCanny, imgDil, kernel, Point(-1, -1), 2); // Dilate the image
	erode(imgDil, imgErode, kernel); // Erode the image
	
	imshow("Image Canny", imgCanny); // Display the Canny edge-detected image
	imshow("Image", image); // Display the original image
	imshow("Image Gray", ImageGrey);
	// Display the grayscale image
	imshow("Image Blur", imgBlur); // Display the blurred image
	imshow("Image Dilation", imgDil); // Display the dilated image
	imshow("Image Erode", imgErode); // Display the eroded image
	waitKey(0); // Wait indefinitely until a key is pressed
}
#endif
// Basic Functions

