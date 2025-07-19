#if 0
#include <opencv2/opencv.hpp> // Include the main OpenCV header
#include <iostream>

int main() {
    // Specify the path to your image file
    const std::string imagePath = "C:\\Users\\sidha\\OneDrive\\Desktop\\pic.jpg";

    // Read the image from the specified path
    // cv::IMREAD_COLOR loads a color image (default)
    // cv::IMREAD_GRAYSCALE loads a grayscale image
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1; // Indicate an error
    }

    // Create a window to display the image
    cv::namedWindow("My Image", cv::WINDOW_AUTOSIZE);

    // Display the image in the created window
    cv::imshow("My Image", image);

    // Wait indefinitely until a key is pressed
    cv::waitKey(0);

    // Destroy all OpenCV windows
    cv::destroyAllWindows();

    return 0; // Indicate successful execution
}
#endif
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cmath>

int main() {
    cv::VideoCapture cap(0); // Open default camera
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    cv::Mat frame, hsvFrame, thresholdedFrame;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // 1. Hand Segmentation (Skin color in HSV)
        cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
        cv::inRange(hsvFrame, cv::Scalar(0, 50, 50), cv::Scalar(20, 255, 255), thresholdedFrame);
        cv::GaussianBlur(thresholdedFrame, thresholdedFrame, cv::Size(5, 5), 0);

        // 2. Contour Detection
        contours.clear();
        hierarchy.clear();
        cv::findContours(thresholdedFrame, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        int fingerCount = 0;
        std::string status = "No hand detected";

        if (!contours.empty()) {
            // Find the largest contour
            double maxArea = 0;
            int handContourIdx = -1;
            for (size_t i = 0; i < contours.size(); ++i) {
                double area = cv::contourArea(contours[i]);
                if (area > maxArea && area > 5000) { // Filter small blobs
                    maxArea = area;
                    handContourIdx = static_cast<int>(i);
                }
            }

            if (handContourIdx != -1) {
                const auto& handContour = contours[handContourIdx];

                std::vector<int> hullIndices;
                cv::convexHull(handContour, hullIndices, false, false); // Get hull indices

                std::vector<cv::Vec4i> defects;
                if (handContour.size() >= 4 && hullIndices.size() >= 4) {
                    cv::convexityDefects(handContour, hullIndices, defects);

                    if (!defects.empty()) {
                        for (const auto& defect : defects) {
                            cv::Point start = handContour[defect[0]];
                            cv::Point end = handContour[defect[1]];
                            cv::Point far = handContour[defect[2]];
                            float depth = defect[3] / 256.0f;

                            double angle = std::acos(
                                ((start - far).dot(end - far)) /
                                (cv::norm(start - far) * cv::norm(end - far))
                            ) * 180 / CV_PI;

                            if (angle < 90 && depth > 10) {
                                fingerCount++;
                                cv::circle(frame, far, 6, cv::Scalar(0, 0, 255), -1);
                            }
                        }
                    }

                    status = "Fingers: " + std::to_string(fingerCount + 1); // +1 for the thumb or primary contour peak

                    // Draw hull and contour
                    std::vector<cv::Point> hullPoints;
                    cv::convexHull(handContour, hullPoints, false, true);
                    cv::drawContours(frame, std::vector<std::vector<cv::Point>>{hullPoints}, -1, cv::Scalar(0, 255, 0), 2);
                    cv::drawContours(frame, contours, handContourIdx, cv::Scalar(255, 0, 0), 2);
                }
                else {
                    status = "Hand contour not sufficient";
                }
            }
        }

        // Display results
        cv::putText(frame, status, cv::Point(30, 50), cv::FONT_HERSHEY_SIMPLEX, 1,
            status.find("Fingers") != std::string::npos ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2);

        cv::imshow("Hand Detection", frame);
        cv::imshow("Thresholded", thresholdedFrame);

        if (cv::waitKey(30) == 27) break; // Exit on 'Esc'
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
