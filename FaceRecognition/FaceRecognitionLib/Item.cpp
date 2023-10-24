
#include "pch.h"
#include "Item.h"

/**
 *COnstructor for Item class
*/
Item::Item(const wxString& filename, FaceRecognition* facrec)
{
	mPath = filename;
	mFaceRecognition = facrec;
}

void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
}

void Item::Process()
{
}

