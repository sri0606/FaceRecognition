#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "FaceDetectionView.h"

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

void FaceDetectionView::AddDetectedFace(std::shared_ptr<wxImage> faceImage)
{
    mDetectedFaces.push_back(faceImage);
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FaceDetectionView::OnPaint(wxPaintEvent& event)
{

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    double x = 10;
    double y = 10;

    for (auto &face : mDetectedFaces) {
        // Calculate the dimensions and aspect ratio
        double width = face->GetWidth();
        double height = face->GetHeight();
        double aspectRatio = width / height;

        // Calculate the new height to fit a specific width (e.g., 100 pixels)
        double newWidth = 100.0;
        double newHeight = newWidth / aspectRatio;

        // Rescale the image with a specific quality option (you can choose the one you prefer)
        wxImage scaledImage = face->Rescale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);

        // Draw the image on the graphics context
        auto bitmap = graphics->CreateBitmapFromImage(scaledImage);
        graphics->DrawBitmap(bitmap, x, y, newWidth, newHeight);

        // Update the position for the next image
        x += newWidth + 10; // Add some spacing between images
    }
}