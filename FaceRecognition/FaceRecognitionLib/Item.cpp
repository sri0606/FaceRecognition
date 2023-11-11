
#include "pch.h"
#include "Item.h"
#include <wx/dcscreen.h>
#include "FaceRecognitionView.h"
#include "FaceRecognition.h"

/**
 *COnstructor for Item class
*/
Item::Item(const wxString& filename, FaceRecognitionView* parent, FaceRecognition* facrec)
{
	mPath = filename;
	mFaceRecognition = facrec;
	mParentView = parent;
}

void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
}

void Item::Process()
{
}

