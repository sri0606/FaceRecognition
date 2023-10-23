#pragma once

#include "Item.h"
/**

*/
class Image: public Item
{

private:
	wxImage mImage;
	wxImage LoadImage(const wxString& imagePath);
public:

	Image(wxWindow* parent, const wxString& filename);
	virtual void Process(wxDC* dc) override;
	virtual void Draw(wxDC* dc) override;
	void SetImage(const wxString& imagePath);

};