#pragma once
#include <opencv2/opencv.hpp>
#include "Item.h"
/**

*/
class Image: public Item
{

private:
	wxImage mImage;
	wxImage LoadImage(const wxString& imagePath);
public:

	Image( const wxString& filename, FaceRecognition* facrec);
	virtual void Process() override;
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void SetImage(const wxString& imagePath);
	virtual void DetectFaces() override;
	virtual void SetFaceRecognition(FaceRecognition* facrec) override{ mFaceRecognition = facrec; }
};