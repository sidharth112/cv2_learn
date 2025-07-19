#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
using namespace std;

//Image
#if 0
int main()
{
	std::string imagePath = "resources/pic.jpg"; // Specify the path to your image file
	Mat image = imread(imagePath, IMREAD_COLOR); // Read the image file
	imshow("Image", image);
	waitKey(0); // Wait indefinitely until a key is pressed
}
#endif
//Video
#if 0
int main()
{
	std::string path = "resources/test_video.mp4";
	VideoCapture cap(path);
	Mat img;
	while (true)
	{
		cap.read(img);
		imshow("Video", img);
		waitKey(20);
		if (waitKey(1) >= 0) // Wait for a key press for 1 ms
		{
			break; // Exit the loop if a key is pressed
		}
	}
}
#endif

//webcam

int main()
{
	VideoCapture cap(0); // Open the default camera (0) for multiple cameras use 0/1 etc
	//VideoCapture cap(path);
	Mat img;
	while (true)
	{
		cap.read(img);
		imshow("Video", img);
		waitKey(20);
		if (waitKey(1) >= 0) // Wait for a key press for 1 ms
		{
			break; // Exit the loop if a key is pressed
		}
	}
}