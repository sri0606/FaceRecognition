
/**
*/

#include "FaceRecognition.h"

/**
 * Class that defines our Aquarium view
 */
class FaceRecognitionView : public wxWindow
{
private:
	/// An object that describes our aquarium
	FaceRecognition mFaceRecognition;
	void OnPaint(wxPaintEvent& event);


public:
	void Initialize(wxFrame*);
	//void OnMouseMove(wxMouseEvent& event);
	//void OnLeftUp(wxMouseEvent& event);
	//void OnLeftDown(wxMouseEvent& event);
	//void OnDoubleClick(wxMouseEvent& event);

	void OnFileOpen(wxCommandEvent& event);
	void OnFileSaveAs(wxCommandEvent& event);
};
