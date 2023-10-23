#include "pch.h"
#include "FaceRecognition.h"
#include <wx/xml/xml.h>
#include <wx/splitter.h>
#include <wx/dcbuffer.h>
#include "Image.h"

using namespace std;

/**
 * FaceRecognition Constructor
 */
FaceRecognition::FaceRecognition(wxWindow* window, wxFrame* frame)
{

}
	
/**
 * Draw the face rec
 * @param dc The device context to draw on
 */
void FaceRecognition::OnDraw(wxDC* dc)
{
	// Set the background color 
	dc->SetBackground(wxColour(0, 255, 0));
	// Clear the device context with the background color
	dc->Clear();
	wxFont font(wxSize(0, 20),
		wxFONTFAMILY_SWISS,
		wxFONTSTYLE_NORMAL,
		wxFONTWEIGHT_NORMAL);
	dc->SetFont(font);
	dc->SetTextForeground(wxColour(0, 64, 0));
	dc->DrawText(L"Under the Sea!", 10, 10);

	if (mItem != nullptr) {
		mItem->Draw(dc);
	}
}


/**
*/
void FaceRecognition::Save(const wxString& filename)
{
}

void FaceRecognition::Load(wxWindow* parent,const wxString& filename)
{
	mItem = std::make_shared<Image>(parent,filename);

}

void FaceRecognition::Clear()
{
}
