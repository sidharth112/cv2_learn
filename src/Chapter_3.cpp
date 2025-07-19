#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <print>
#include "Chapter_3.h"


using namespace cv;
using namespace std;

//Resize and crop images
#if 1
int main()
{
	std::string imagePath = "resources/pic.jpg"; // Specify the path to your image file
	Mat image = imread(imagePath, IMREAD_COLOR); // Read the image file
	Mat imgResize, imgCrop;
	Rect roi(50, 50, 50, 50); // Define a region of interest (ROI) for cropping
	if (roi.x + roi.width > image.cols || roi.y + roi.height > image.rows) {
		std::cerr << "Error: ROI exceeds image dimensions." << std::endl;
		return -1;
	}

	resize(image, imgResize, Size(), 2,2);
	imgCrop = image(roi); // Crop the image from (100, 100) with a size of 300x300 pixels
	cout << "Image Size: " << image.size() << endl; // Print the width of the image
	imshow("Image", image); // Display the  image
	imshow("Image", image);
	imshow("Image Crop", imgCrop);
	waitKey(0); // Wait indefinitely until a key is pressed
}
#endif
// Basic Functions