#include "pch.h"
#include "LoadingPanel.h"
#include <wx\graphics.h>
#include <wx/dcbuffer.h>

const std::wstring loadImagePath = L"images/load.png";

LoadingPanel::LoadingPanel(wxFrame* parent):wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
{
	// Add graphics, additional information, or any design you want
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &LoadingPanel::OnPaint, this);
}

void LoadingPanel::OnPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);

    const wxSize& size = GetClientSize();
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    // clear background of the window with black
    gc->SetBrush(*wxBLACK_BRUSH);

    wxImage image(loadImagePath, wxBITMAP_TYPE_PNG);

    int centerX = (size.x - image.GetWidth()) / 2;
    int centerY = (size.y - image.GetHeight()) / 2;

    // Create a bitmap from the loaded image
    wxBitmap bitmap(image);

    // Paint the image at the calculated position
    gc->DrawBitmap(bitmap, centerX, centerY,image.GetWidth(),image.GetHeight());
    
}

