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
	int mCurrentFrameIndex=0;
	
	std::vector<wxBitmap> mFrames;
	
public:

	Video(const wxString& filename, FaceRecognitionView* parent, FaceRecognition* facrec);
	virtual void Process() override;
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	virtual void DetectFaces() override;
	void AddCurrentFrame(cv::Mat currentMatFrame);
	virtual void Update() override;
};