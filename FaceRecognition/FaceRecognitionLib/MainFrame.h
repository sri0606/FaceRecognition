#pragma once

class FaceRecognitionView;
class FaceDetectionView;
/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
	FaceRecognitionView* mFaceRecognitionView;
	FaceDetectionView* mFaceDetectionView;
public:
	void Initialize();

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
