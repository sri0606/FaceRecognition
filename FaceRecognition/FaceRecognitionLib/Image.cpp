
#include "pch.h"
#include "Image.h"
#include <opencv2/core/core.hpp>

int main()
{
	std::string path = "/images/fac_rec_logo.ico";
	cv::Mat image = cv::imread(path, IMREAD_COLOR);
	imshow("Image", image);
	waitKey(0);


	return 0;

}