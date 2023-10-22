#include "pch.h"
#include "FaceRecognition.h"
#include <wx/xml/xml.h>
#include "Image.h"

using namespace std;

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

	/*for (auto item : mItems)
	{
		item->Draw(dc);

	}*/
}

/**
 * FaceRecognition Constructor
 */
FaceRecognition::FaceRecognition()
{
	/*mBackground = make_unique<wxBitmap>(
		L"images/background1.png", wxBITMAP_TYPE_ANY);*/
}

/**
*/
void FaceRecognition::Save(const wxString& filename)
{
}

void FaceRecognition::Load(const wxString& filename)
{
	mImage = new Image(filename);
}

void FaceRecognition::Clear()
{
}
