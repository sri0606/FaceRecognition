#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "FaceDetectionView.h"
#include "convertmattowxbmp.h"

/**
 * Constructor
 * @param parent The main wxFrame object
 * 
 */
FaceDetectionView::FaceDetectionView(wxFrame* parent) :
    wxScrolledCanvas(parent,
        wxID_ANY,
        wxDefaultPosition,
        wxSize(100, 180),
        wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &FaceDetectionView::OnPaint, this);
    //Bind(wxEVT_LEFT_DOWN, &FaceDetectionView::OnLeftDown, this);
    //Bind(wxEVT_LEFT_UP, &FaceDetectionView::OnLeftUp, this);
    //Bind(wxEVT_MOTION, &FaceDetectionView::OnMouseMove, this);

}

/**
 * Force an update of this window when the picture changes.
 */
void FaceDetectionView::UpdateObserver()
{
    Refresh();
    Update();
}

void FaceDetectionView::AddDetectedFace(cv::Mat faceImage)
{
    mDetectedFaces.push_back(faceImage);
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FaceDetectionView::OnPaint(wxPaintEvent& event)
{
    SetVirtualSize(10, 0);
    SetScrollRate(1, 0);
    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
    // Get the dimensions of the graphics context
    double contextWidth, contextHeight;
    graphics->GetSize(&contextWidth, &contextHeight);

    double x = 10;
    double y = 10;

    double scaleX, scaleY, scaleFactor = 0;
    int newWidth, newHeight;

    for (auto &face : mDetectedFaces) {
        
        //Calculate the scaling factors to fit the image within the context while maintaining aspect ratio
        scaleX = contextWidth / face.cols;
        scaleY = contextHeight / face.rows;
        scaleFactor = std::min(scaleX, scaleY);

        // Calculate the new dimensions
        newWidth = static_cast<int>(face.cols * scaleFactor);
        newHeight = static_cast<int>(face.rows * scaleFactor);

        wxBitmap bitmap(face.cols,face.rows,24);
        ConvertMatBitmapTowxBitmap(face,bitmap);
        graphics->DrawBitmap(bitmap, x, y, newWidth, newHeight);

        // Update the position for the next image
        x += newWidth + 5; // Add some spacing between images
    }
}