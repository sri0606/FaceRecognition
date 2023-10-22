
#include "pch.h"
#include "Image.h"
#include <opencv2/opencv.hpp>

using namespace cv;

/**
 * FaceRecognition Constructor
 */
Image::Image(const wxString& filename)
{
	mPath = filename;

    cv::Mat originalImage = cv::imread(mPath.ToStdString());

    // Convert the image to grayscale
    cv::Mat grayscaleImage;
    cv::cvtColor(originalImage, grayscaleImage, cv::COLOR_BGR2GRAY);

    // Create a window to display the original image
    cv::namedWindow("Original Image", cv::WINDOW_NORMAL);
    cv::imshow("Original Image", originalImage);

    // Create a window to display the grayscale image
    cv::namedWindow("Grayscale Image", cv::WINDOW_NORMAL);
    cv::imshow("Grayscale Image", grayscaleImage);

    // Wait for a key press and then close the windows
    cv::waitKey(0);
    cv::destroyAllWindows();
}

