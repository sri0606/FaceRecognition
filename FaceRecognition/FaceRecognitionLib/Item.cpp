
#include "pch.h"
#include "Item.h"

/**
 *COnstructor for Item class
*/
Item::Item(wxWindow* parent, const wxString& filename)
{
	mPath = filename;
}

void Item::Draw(wxDC* dc)
{
}

void Item::Process(wxDC* dc)
{
}

