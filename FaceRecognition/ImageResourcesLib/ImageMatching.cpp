
#include "ImageMatching.h"


/**
** Feature matching in images usong OpenCV's SIFT and knn match
*/
bool CompareImagesByFeatureMatching(const wxBitmap& bitmap1, const wxBitmap& bitmap2, int threshold) {
    // Convert wxBitmap to cv::Mat
    wxImage image1 = bitmap1.ConvertToImage();
    wxImage image2 = bitmap2.ConvertToImage();
    cv::Mat img1(image1.GetHeight(), image1.GetWidth(), CV_8UC3, image1.GetData());
    cv::Mat img2(image2.GetHeight(), image2.GetWidth(), CV_8UC3, image2.GetData());

    // Convert images to grayscale
    cv::Mat gray1, gray2;
    cv::cvtColor(img1, gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2, gray2, cv::COLOR_BGR2GRAY);

    // Detect features and perform matching
    cv::Ptr<cv::Feature2D> detector = cv::SIFT::create();
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;

    detector->detectAndCompute(gray1, cv::noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(gray2, cv::noArray(), keypoints2, descriptors2);

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    std::vector<std::vector<cv::DMatch>> knn_matches;
    matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);

    // Ratio test to filter good matches
    const float ratio_thresh = 0.7f;
    std::vector<cv::DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++) {
        if (knn_matches[i][0].distance < ratio_thresh* knn_matches[i][1].distance) {
            good_matches.push_back(knn_matches[i][0]);
        }
    }

    // If the number of good matches is above the threshold, consider the images similar
    return good_matches.size() > threshold;
}


/**
Image matching using Bhattacharya distance
*/
bool CompareImagesByHistogram(const wxBitmap& bitmap1, const wxBitmap& bitmap2, double threshold) {
    // Convert wxBitmap to cv::Mat
    wxImage image1 = bitmap1.ConvertToImage();
    wxImage image2 = bitmap2.ConvertToImage();
    cv::Mat img1(image1.GetHeight(), image1.GetWidth(), CV_8UC3, image1.GetData());
    cv::Mat img2(image2.GetHeight(), image2.GetWidth(), CV_8UC3, image2.GetData());

    // Convert images to grayscale
    cv::Mat gray1, gray2;
    cv::cvtColor(img1, gray1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2, gray2, cv::COLOR_BGR2GRAY);

    // Calculate histograms
    cv::Mat hist1, hist2;
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };

    cv::calcHist(&gray1, 1, 0, cv::Mat(), hist1, 1, &histSize, &histRange);
    cv::calcHist(&gray2, 1, 0, cv::Mat(), hist2, 1, &histSize, &histRange);

    // Normalize histograms
    cv::normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    // Calculate Bhattacharyya distance
    double bhattacharyya = cv::compareHist(hist1, hist2, cv::HISTCMP_BHATTACHARYYA);

    // If the Bhattacharyya distance is below the threshold, consider the images similar
    return bhattacharyya < threshold;
}
