
#include "pch.h"
#include "FaceRecognitionView.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "FaceRecognition.h"

FaceRecognitionView::FaceRecognitionView(wxPanel* parent) :
	wxScrolledCanvas(parent,
		wxID_ANY)
{
	
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &FaceRecognitionView::OnPaint, this);

	parent->GetParent()->Bind(wxEVT_COMMAND_MENU_SELECTED, &FaceRecognitionView::OnFileSaveAs, this, wxID_SAVEAS);
	parent->GetParent()->Bind(wxEVT_COMMAND_MENU_SELECTED, &FaceRecognitionView::OnFileOpen, this, wxID_OPEN);
}

void FaceRecognitionView::UpdateObserver()
{
	Refresh();
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
	mFaceRecognition->ClearDetectedFaces();
	mFaceRecognition->Load(filename);
	mFaceRecognition->UpdateObservers();
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
	DoPrepareDC(dc);

	// Clear the image to black
	wxBrush background(*wxBLACK);
	dc.SetBackground(background);
	dc.Clear();

	// Create a graphics context
	auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
	graphics->DrawRectangle(0, 0, GetSize().x, GetSize().y);

	mFaceRecognition->OnDraw(graphics);
}

