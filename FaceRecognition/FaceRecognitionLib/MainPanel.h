#pragma once


class FaceRecognitionView;
class FaceDetectionView;

class MainPanel : public wxPanel 
{
private:
	FaceRecognitionView* mFaceRecognitionView;
	FaceDetectionView* mFaceDetectionView;
public:
	MainPanel(wxFrame* parent);
};