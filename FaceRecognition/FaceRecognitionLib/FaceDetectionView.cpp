#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "FaceDetectionView.h"
#include "Observer.h"

/**
 * Constructor
 * @param parent The main wxFrame object
 * 
 */
FaceDetectionView::FaceDetectionView(wxPanel* parent) : Observer(parent),
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


/**
* File>Open Image handler
 * @param event Menu event
*/
void FaceDetectionView::OnImageOpen(wxCommandEvent& event)
{
    UpdateObserver();
}

/**
* File>Open Video handler
 * @param event Menu event
*/
void FaceDetectionView::OnVideoOpen(wxCommandEvent& event)
{
    UpdateObserver();
}

void FaceDetectionView::OnFileSaveAs(wxCommandEvent& event)
{
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
    // Get the dimensions of the graphics context
    double contextWidth, contextHeight;
    graphics->GetSize(&contextWidth, &contextHeight);
    
    int minImageWidth = 250;
    int minImageHeight = 275;

    auto pair = GetNumofRowsCols(contextWidth, contextHeight);

    int rows = pair.first;
    int cols = pair.second;

    SetVirtualSize(1.5*contextWidth, rows*(contextHeight+5));
    SetScrollRate(10, 10);

    double x = 10;
    double y = 10;
    int i = 1;
    auto detectedFaces = mFaceRecognition->GetDetectedFaces();
    for (auto &face : detectedFaces) {

        graphics->DrawBitmap(face, x, y, minImageWidth, minImageHeight);

        if (i < cols) {
            // Update the position for the next image
            x += minImageWidth + 5;
            i++;
        }
        else {
            x = 10;
            y = minImageHeight+5;
            i = 0;
        }   
    }
}

std::pair<int,int> FaceDetectionView::GetNumofRowsCols(int contextWidth, int contextHeight) {
    int minImageWidth = 250;
    int minImageHeight = 275;
    int maxImageWidth = contextWidth;
    int maxImageHeight = contextHeight;
    int numFaces = mFaceRecognition->GetNumofDetectedFaces();

    int rows=1;
    int columns = 8;

    int maxScrollLengthHorizontal = 1.5*contextWidth;
    // 8 * 50 > 300
    if (numFaces * minImageWidth > maxScrollLengthHorizontal) {
        rows = static_cast<int>(numFaces * minImageWidth / maxScrollLengthHorizontal);
    }
    return std::pair<int,int>(rows, columns);
}