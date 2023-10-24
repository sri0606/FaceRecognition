#pragma once

#include "Observer.h"

/**
 * Class that defines our Aquarium view
 */
class FaceRecognitionView final : public wxScrolledCanvas, public Observer
{
private:
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


	/**
	 * Add the face that has been detected
	*/
	virtual void AddDetectedFace(std::shared_ptr<wxImage> faceImage) {}
};
