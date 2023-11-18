
#include "pch.h"
#include "FaceRecognitionView.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "FaceRecognition.h"
#include "Observer.h"
#include "ids.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

FaceRecognitionView::FaceRecognitionView(wxPanel* parent) : Observer(parent),
	wxScrolledCanvas(parent,
		wxID_ANY)
{
	
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	Bind(wxEVT_PAINT, &FaceRecognitionView::OnPaint, this);

	parent->GetParent()->Bind(wxEVT_COMMAND_MENU_SELECTED, &FaceRecognitionView::OnFileSaveAs, this, wxID_SAVEAS);
	parent->GetParent()->Bind(wxEVT_COMMAND_MENU_SELECTED, &FaceRecognitionView::OnImageOpen, this, IDM_OPENIMAGE);
	parent->GetParent()->Bind(wxEVT_COMMAND_MENU_SELECTED, &FaceRecognitionView::OnVideoOpen, this, IDM_OPENVIDEO);
	Bind(wxEVT_TIMER, &FaceRecognitionView::OnTimer, this);

	mTimer.SetOwner(this);
	mTimer.Start(FrameDuration);

	mStopWatch.Start();
}

void FaceRecognitionView::UpdateObserver()
{
	Refresh();
}

/**
* File>Open menu handler
 * @param event Menu event
*/
void FaceRecognitionView::OnImageOpen(wxCommandEvent& event)
{
	wxFileDialog loadFileDialog(this, L"Load Image", L"", L"",
		L"Image Files|*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.tiff;*.ico|All Files|*.*", wxFD_OPEN);

	if (loadFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}
	auto filename = loadFileDialog.GetPath();
	mFaceRecognition->ClearDetectedFaces();
	mFaceRecognition->LoadImage(this,filename);
	mFaceRecognition->UpdateObservers();
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void FaceRecognitionView::OnVideoOpen(wxCommandEvent& event)
{
	wxFileDialog loadFileDialog(this, L"Load Video", L"", L"",
		L"Video Files|*.mp4;*.avi;*.mkv;*.mov;*.wmv;*.flv|All Files|*.*", wxFD_OPEN);

	if (loadFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}
	auto filename = loadFileDialog.GetPath();
	mFaceRecognition->ClearDetectedFaces();
	mFaceRecognition->LoadVideo(this, filename);
	mFaceRecognition->UpdateObservers();
}


void FaceRecognitionView::OnFileSaveAs(wxCommandEvent& event)
{
}

/**
 * Event handler for wxEVT_TIMER
 * @param event Timer event
 */
void FaceRecognitionView::OnTimer(wxTimerEvent& event)
{
	mFaceRecognition->UpdateObservers();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void FaceRecognitionView::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	DoPrepareDC(dc);

	// Compute the time that has elapsed
	// since the last call to OnPaint.
	auto newTime = mStopWatch.Time();
	auto elapsed = (double)(newTime - mTime) * 0.001;
	mTime = newTime;
	if (mFaceRecognition!=nullptr)
		mFaceRecognition->Update();

	// Clear the image to black
	wxBrush background(*wxBLACK);
	dc.SetBackground(background);
	dc.Clear();

	// Create a graphics context
	auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
	graphics->DrawRectangle(0, 0, GetSize().x, GetSize().y);

	mFaceRecognition->OnDraw(graphics);
}

