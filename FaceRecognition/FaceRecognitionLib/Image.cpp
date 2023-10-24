
#include "pch.h"
#include "Image.h"
#include <opencv2/opencv.hpp>
#include <wx/splitter.h>
#include <wx/graphics.h>
#include "Item.h"
#include "FaceRecognition.h"
using namespace cv;


/**
 * Image Constructor
 */
Image::Image(const wxString& filename, FaceRecognition* facrec):Item(filename, facrec)
{
    this->SetImage(filename);
   
}

/**
* Process the image to customize it to as needed
*/
void Image::Process()
{
    cv::Mat originalImage = cv::imread(mPath.ToStdString());

    if (originalImage.empty()) {
        wxLogError("Failed to load the image from path: %s", mPath);
        return;
    }

    // Convert the OpenCV image to a wxImage
    mImage = wxImage(originalImage.cols, originalImage.rows, originalImage.data, true);
    if (!mImage.IsOk()) {
        wxLogError("Failed to convert OpenCV image to wxImage.");
        return;
    }
}


void Image::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Get the dimensions of the graphics context
    double contextWidth, contextHeight;
    graphics->GetSize(&contextWidth, &contextHeight);

    // Calculate the scaling factors to fit the image within the context while maintaining aspect ratio
    double scaleX = contextWidth / mImage.GetWidth();
    double scaleY = contextHeight / mImage.GetHeight();
    double scaleFactor = std::min(scaleX, scaleY);

    // Calculate the new dimensions
    int newWidth = static_cast<int>(mImage.GetWidth() * scaleFactor);
    int newHeight = static_cast<int>(mImage.GetHeight() * scaleFactor);

    // Rescale the image with a specific quality option (you can choose the one you prefer)
    wxImage scaledImage = mImage.Rescale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);

    // Create a bitmap from the scaled image
    auto bitmap = graphics->CreateBitmapFromImage(scaledImage);
    graphics->DrawBitmap(bitmap, 0, 0, newWidth, newHeight);

}


void Image::SetImage(const wxString& imagePath)
{
    // Load the image using the provided path
    mImage = LoadImage(imagePath);

    DetectFaces();
}

/**
*   Detect the faces in the image
*/
void Image::DetectFaces()
{
    // Load an image
    cv::Mat image = cv::imread(mPath.ToStdString());
    if (image.empty()) {
        std::cerr << "Image not found. Make sure to provide a valid image path." << std::endl;
        return;
    }
    
    // Initialize face detection classifier
    cv::CascadeClassifier face_cascade;
    // Load pre-trained XML classifier for face detection
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade." << std::endl;
        return ;
    }

    // Convert the image to grayscale for detection
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray_image, gray_image);

    // Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 3, 0);

    // Extract and display detected faces
    for (size_t i = 0; i < faces.size(); i++) {
        // Crop the detected face region
        cv::Mat face = image(faces[i]);

        wxImage* wxImg = MatToImage(face);
        std::shared_ptr<wxImage> wxImgShared(wxImg); // Convert to shared_ptr
        mFaceRecognition->AddDetectedFaces(wxImgShared);

        // Optionally, you can save each face as a separate image
        std::string face_filename = "face_" + std::to_string(i) + ".jpg";
        cv::imwrite(face_filename, face);

    }
    // Display the original image with rectangles around detected faces
    for (const auto& face : faces) {
        cv::rectangle(image, face, cv::Scalar(0, 0, 255), 2);
    }
    mImage = *MatToImage(image);
}




// Function to convert a cv::Mat to wxImage
wxImage* Image::MatToImage(const cv::Mat& mat) {
    if (mat.empty()) {
        return nullptr; // Return an empty image if the input is empty
    }

    cv::Mat rgbMat; // Create an RGB version of the image (if it's not in RGB format)
    if (mat.channels() == 1) {
        cv::cvtColor(mat, rgbMat, cv::COLOR_GRAY2BGR);
    }
    else {
        rgbMat = mat;
    }

    auto image = new wxImage(rgbMat.cols, rgbMat.rows, rgbMat.data, true); // Create a wxImage from the pixel data
    return image;
}


wxImage Image::LoadImage(const wxString& imagePath)
{
    // Load the image from the provided path
    wxImage img(imagePath, wxBITMAP_TYPE_ANY);

    if (!img.IsOk()) {
        // Handle image loading error
        wxLogError("Failed to load image: %s", imagePath);
    }

    return img;
}
