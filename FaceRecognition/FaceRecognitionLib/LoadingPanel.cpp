#include "pch.h"
#include "LoadingPanel.h"

LoadingPanel::LoadingPanel(wxFrame* parent):wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
{
	// Add graphics, additional information, or any design you want
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &LoadingPanel::OnPaint, this);
}

void LoadingPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // Set the background color
    dc.SetBackground(*wxBLUE_BRUSH); // Replace wxBLUE_BRUSH with your desired color

    // Clear the background with the chosen color
    dc.Clear();

    // Draw a red rectangle (you can replace this with your custom graphics)
    dc.SetBrush(*wxRED_BRUSH);
    dc.SetPen(*wxTRANSPARENT_PEN); // No outline
    dc.DrawRectangle(50, 50, 100, 100);
}