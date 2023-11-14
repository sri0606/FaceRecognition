#pragma once

#include "Item.h"

/**

*/
class Image: public Item
{

private:
	//original image
	wxImage mImage;
	//image with the detected faces highlighted
	wxBitmap mImageDetected;
public:

	Image( const wxString& filename, FaceRecognitionView* parent, FaceRecognition* facrec);
	virtual void Process() override;
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	virtual void DetectFaces() override;
};