
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

/**
* File>Open menu handler
 * @param event Menu event
*/
void FaceRecognitionView::OnFileOpen(wxCommandEvent& event)
{
	wxFileDialog loadFileDialog(this, L"Load Image", L"", L"",
		L"Image Files|*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.tiff;*.ico|All Files|*.*", wxFD_OPEN);

	if (loadFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	auto filename = loadFileDialog.GetPath();
	mFaceRecognition.Load(filename);
	Refresh();
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