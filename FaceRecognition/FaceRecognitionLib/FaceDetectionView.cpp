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
}