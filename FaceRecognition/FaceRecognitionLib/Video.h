#pragma once

#include "Item.h"
#include <wx/mediactrl.h>
/**

*/
class Video : public Item
{
private:
	//original video
	wxMediaCtrl* mVideo;
	//image with the detected faces highlighted
	//wxBitmap mImageDetected;
	
public:

	Video(const wxString& filename, FaceRecognitionView* parent, FaceRecognition* facrec);
	virtual void Process() override;
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void SetVideo(const wxString& VideoPath);
	wxMediaCtrl* LoadVideo(const wxString& VideoPath);
	virtual void DetectFaces() override;
};