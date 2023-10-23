#pragma once

#include "Observer.h"
class FaceRecognition;

/**
 * Class that defines our Aquarium view
 */
class FaceRecognitionView final : public wxScrolledCanvas, public Observer
{
private:
	/// An object that describes our aquarium
	FaceRecognition* mFaceRecognition;
	void OnPaint(wxPaintEvent& event);


public:
	FaceRecognitionView(wxFrame* parent);
	//void OnMouseMove(wxMouseEvent& event);
	//void OnLeftUp(wxMouseEvent& event);
	//void OnLeftDown(wxMouseEvent& event);
	//void OnDoubleClick(wxMouseEvent& event);

	void UpdateObserver() override;

	void OnFileOpen(wxCommandEvent& event);
	void OnFileSaveAs(wxCommandEvent& event);
};
