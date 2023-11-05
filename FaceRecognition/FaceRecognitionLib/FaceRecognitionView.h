#pragma once

#include "Observer.h"

/**
 * Class that defines our Aquarium view
 */
class FaceRecognitionView final : public wxScrolledCanvas, public Observer
{
private:
	virtual void OnPaint(wxPaintEvent& event) override;


public:
	FaceRecognitionView(wxPanel* parent);
	//void OnMouseMove(wxMouseEvent& event);
	//void OnLeftUp(wxMouseEvent& event);
	//void OnLeftDown(wxMouseEvent& event);
	//void OnDoubleClick(wxMouseEvent& event);

	void UpdateObserver() override;

	virtual void OnFileOpen(wxCommandEvent& event) override;
	virtual void OnFileSaveAs(wxCommandEvent& event) override;
};
