#pragma once

# include <iostream>
#include "Image.h"

class FaceRecognition
{
private:
	std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use
	Image* mImage;

public:
	void OnDraw(wxDC* dc);
	FaceRecognition();
	void Save(const wxString& filename);
	void Load(const wxString& filename);
	void Clear();
};