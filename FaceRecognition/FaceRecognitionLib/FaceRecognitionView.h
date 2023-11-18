#pragma once

#include "Observer.h"

/**
 * Class that defines our FaceRecognitionView view
 */
class FaceRecognitionView final : public wxScrolledCanvas, public Observer
{
private:

	/// The timer that allows for animation
	wxTimer mTimer;

	/// Stopwatch used to measure elapsed time
	wxStopWatch mStopWatch;

	/// The last stopwatch time
	long mTime = 0;

	virtual void OnPaint(wxPaintEvent& event) override;

public:
	FaceRecognitionView(wxPanel* parent);
	//void OnMouseMove(wxMouseEvent& event);
	//void OnLeftUp(wxMouseEvent& event);
	//void OnLeftDown(wxMouseEvent& event);
	//void OnDoubleClick(wxMouseEvent& event);

	void UpdateObserver() override;

	virtual void OnImageOpen(wxCommandEvent& event) override;
	virtual void OnVideoOpen(wxCommandEvent& event) override;
	virtual void OnFileSaveAs(wxCommandEvent& event) override;

	void OnTimer(wxTimerEvent& event);

};
