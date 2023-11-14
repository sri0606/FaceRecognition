#include "pch.h"
#include "Video.h"
#include <chrono>
#include <thread>
#include <wx/splitter.h>
#include <wx/graphics.h>
#include <opencv2/opencv.hpp>
#include "FaceRecognition.h"
#include "FaceRecognitionView.h"
#include "../ImageResourcesLib/convertmattowxbmp.h"

using namespace cv; 

const std::string faceCascadePath = "C:/Program Files/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";

/**
 * Video Constructor
 */
Video::Video(const wxString& filename, FaceRecognitionView* parent, FaceRecognition* facrec) :Item(filename,parent, facrec)
{
    //parent->Bind(wxEVT_TIMER, &Video::SetCurrentFrame, this);
    //mTimer.SetOwner(parent);
    
}

/**
* Process the image to customize it to as needed
*/
void Video::Process()
{
   
   /* mVideo = new wxMediaCtrl(mParentView->GetParentPanel(), wxID_ANY, mPath,
                        wxDefaultPosition, wxDefaultSize,0);*/
    DetectFaces();
}


void Video::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Get the dimensions of the graphics context
    double contextWidth, contextHeight;
    graphics->GetSize(&contextWidth, &contextHeight);

    // Half-width of the window
    int halfWidth = static_cast<int>(contextWidth / 2.0);


    // Calculate the scaling factors to fit the video within the context while maintaining aspect ratio
    double scaleX = halfWidth / static_cast<double>(mCurrentVideoFrame.GetWidth());
    double scaleY = contextHeight / static_cast<double>(mCurrentVideoFrame.GetHeight());
    double scaleFactor = std::min(scaleX, scaleY);

    int newWidth = static_cast<int>(mCurrentVideoFrame.GetWidth() * scaleFactor);
    int newHeight = static_cast<int>(mCurrentVideoFrame.GetHeight() * scaleFactor);

    // Calculate the position to center the video in the context
    int xPos = halfWidth - newWidth / 2;
    int yPos = static_cast<int>((contextHeight - newHeight) / 2);

    // Draw the video frame on the graphics context
    graphics->DrawBitmap(mCurrentVideoFrame, xPos, yPos, newWidth, newHeight);

}

// Event handler 
void Video::SetCurrentFrame()//(wxTimerEvent& event)
{
    if (!mCurrentMatframe.empty()) {
        mCurrentVideoFrame = wxBitmap(mCurrentMatframe.cols, mCurrentMatframe.rows, 24);
        ConvertMatBitmapTowxBitmap(mCurrentMatframe, mCurrentVideoFrame);
        mFaceRecognition->UpdateObservers();
        //mFaceRecognition->ClearDetectedFaces();
    }
}
    
/**
*   Detect the faces in the image
*/
void Video::DetectFaces()
{
    // Open a video file or a camera stream
    cv::VideoCapture videoCapture(mPath.ToStdString());  // or use 0 for the default camera

    // Check if the video/camera opened successfully
    if (!videoCapture.isOpened()) {
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
    //use fps
    //mTimer.Start(1000 / 30);

    // Set the desired frames per second
    const int desiredFPS = 20;
    const std::chrono::milliseconds frameDelay(1000 / desiredFPS);

    while (true) {
        auto start = std::chrono::high_resolution_clock::now();  // Record the start time

        // Read a frame from the video stream
        videoCapture >> mCurrentMatframe;

        // Break the loop if the video is over
        if (mCurrentMatframe.empty()) {
            break;
        }

        // Convert the frame to grayscale for detection
        cv::Mat gray_frame;
        cv::cvtColor(mCurrentMatframe, gray_frame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray_frame, gray_frame);

        // Detect faces
        std::vector<cv::Rect> faces;
        auto minSize = cv::Size(140,100);
        auto maxSize = cv::Size(480,270);
        face_cascade.detectMultiScale(gray_frame, faces, 1.1, 3, 0, minSize, maxSize);

        // Loop through the detected faces and draw bounding boxes
        for (const cv::Rect& face : faces) {
            cv::rectangle(mCurrentMatframe, face, cv::Scalar(0, 0, 255), 1);  // Draw a red rectangle around the face
        }

        // Extract and display detected faces (if needed)
        for (size_t i = 0; i < faces.size(); i++) {
            // Crop the detected face region
            cv::Mat detected_face = mCurrentMatframe(faces[i]);
            mFaceRecognition->AddDetectedFace(detected_face);
        }
        
        // Calculate the time taken for processing
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        // Introduce a delay to achieve the desired FPS
        auto remainingTime = frameDelay - duration;
        if (remainingTime > std::chrono::milliseconds(0)) {
            std::this_thread::sleep_for(remainingTime);
        }

        SetCurrentFrame();
    }
    //mTimer.Stop();
    // Release the VideoCapture
    videoCapture.release();
}
