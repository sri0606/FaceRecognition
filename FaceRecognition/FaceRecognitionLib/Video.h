#pragma once

#include <wx/bitmap.h>
#include <wx/mediactrl.h>
#include "Item.h"


/**

*/
class Video : public Item
{
private:
	//image with the detected faces highlighted
	wxBitmap mCurrentVideoFrame;

	cv::Mat mCurrentMatframe;
	//wxTimer mTimer;
	
public:

	Video(const wxString& filename, FaceRecognitionView* parent, FaceRecognition* facrec);
	virtual void Process() override;
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	virtual void DetectFaces() override;
	void SetCurrentFrame();// wxTimerEvent& event);
};