#pragma once

# include <iostream>

class FaceRecognition
{
private:
	std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

public:
	void OnDraw(wxDC* dc);
	FaceRecognition();
};