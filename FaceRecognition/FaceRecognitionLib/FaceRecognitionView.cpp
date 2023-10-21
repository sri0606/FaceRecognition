
#include "pch.h"
#include "FaceRecognitionView.h"
#include <wx/dcbuffer.h>

void FaceRecognitionView::Initialize(wxFrame* parent)
{
	Create(parent, wxID_ANY);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &FaceRecognitionView::OnPaint, this);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &FaceRecognitionView::OnFileSaveAs, this, wxID_SAVEAS);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &FaceRecognitionView::OnFileOpen, this, wxID_OPEN);
}

void FaceRecognitionView::OnFileOpen(wxCommandEvent& event)
{
}

void FaceRecognitionView::OnFileSaveAs(wxCommandEvent& event)
{
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FaceRecognitionView::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);


	wxBrush background(*wxBLACK);
	dc.SetBackground(background);
	dc.Clear();

	//mAquarium.OnDraw(&dc);
}