#pragma once
#include <wx/dcscreen.h>

/**
*Base class for the items taht are detectable using OpenCV library
*/
class Item
{
protected:
    wxString mPath;
public:
    Item(wxWindow* parent, const wxString& filename);
    Item() = delete; // Disable the default constructor.
    Item(const Item&) = delete; // Disable the copy constructor.
    Item& operator=(const Item&) = delete; // Disable the copy assignment operator.

    virtual void Draw(wxDC* dc);
    virtual void Process(wxDC* dc);
};