#include "pch.h"
#include "Video.h"
#include <wx/splitter.h>
#include <wx/graphics.h>
#include <opencv2/opencv.hpp>
#include "FaceRecognition.h"
#include "FaceRecognitionView.h"
#include "convertmattowxbmp.h"
using namespace cv;

const std::string faceCascadePath = "C:/Program Files/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";

/**
 * Image Constructor
 */
Video::Video(const wxString& filename, FaceRecognitionView* parent, FaceRecognition* facrec) :Item(filename,parent, facrec)
{
    this->SetVideo(filename);

}

/**
* Process the image to customize it to as needed
*/
void Video::Process()
{
    cv::Mat originalVideo = cv::imread(mPath.ToStdString());

    if (originalVideo.empty()) {
        wxLogError("Failed to load the image from path: %s", mPath);
        return;
    }
}


void Video::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Get the dimensions of the graphics context
    double contextWidth, contextHeight;
    graphics->GetSize(&contextWidth, &contextHeight);

    // half-width of window
    int halfWidth = static_cast<int>(contextWidth / 2.0);

    //// Calculate the scaling factors to fit the image within the context while maintaining aspect ratio
    //double scaleX = halfWidth / mVideo.GetWidth();
    //double scaleY = contextHeight / mVideo.GetHeight();
    //double scaleFactor = std::min(scaleX, scaleY);

    //int newWidth, newHeight;
    //// Calculate the new dimensions
    //if (scaleFactor == 0) {
    //    //if the the image dimension are very large extending the window size
    //    newWidth = halfWidth * 0.98;
    //    newHeight = contextHeight;
    //}
    //else {
    //    newWidth = static_cast<int>(mImage.GetWidth() * scaleFactor);
    //    newHeight = static_cast<int>(mImage.GetHeight() * scaleFactor);
    //}

    //

}


void Video::SetVideo(const wxString& VideoPath)
{
    // Load the image using the provided path
    mVideo = LoadVideo(VideoPath);
    DetectFaces();
}

/**
*   Detect the faces in the image
*/
void Video::DetectFaces()
{
    // Open a video file or a camera stream
    cv::VideoCapture cap(mPath.ToStdString());  // or use 0 for the default camera

    // Check if the video/camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream or file!" << std::endl;
        return;
    }

    // Initialize face detection classifier
    cv::CascadeClassifier face_cascade;
    // Load pre-trained XML classifier for face detection
    if (!face_cascade.load(faceCascadePath)) {
        std::cerr << "Error loading face cascade." << std::endl;
        return;
    }

    while (true) {
        // Read a frame from the video stream
        cv::Mat frame;
        cap >> frame;

        // Break the loop if the video is over
        if (frame.empty())
            break;

        // Convert the frame to grayscale for detection
        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray_frame, gray_frame);

        // Detect faces
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray_frame, faces, 1.1, 3, 0);

        // Loop through the detected faces and draw bounding boxes
        for (const cv::Rect& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 0, 255), 3);  // Draw a red rectangle around the face
        }

        // Extract and display detected faces (if needed)
        for (size_t i = 0; i < faces.size(); i++) {
            // Crop the detected face region
            cv::Mat detected_face = frame(faces[i]);
            mFaceRecognition->AddDetectedFace(detected_face);
        }

        // Display the frame with detected faces
        cv::imshow("Detected Faces", frame);

        // Break the loop if the 'ESC' key is pressed
        if (cv::waitKey(30) == 27)
            break;
    }

    // Release the VideoCapture and close any open windows
    cap.release();
    cv::destroyAllWindows();
}


wxMediaCtrl* Video::LoadVideo(const wxString& VideoPath)
{
    wxMediaCtrl* mediaCtrl = new wxMediaCtrl(mParentView->GetParentPanel(), wxID_ANY, VideoPath,
                        wxDefaultPosition, wxDefaultSize,0);

    return mediaCtrl;
}
