#include "pch.h"
#include "MainPanel.h"
#include "MainFrame.h"
#include "FaceRecognitionView.h"
#include "FaceDetectionView.h"
#include "ids.h"
#include "FaceRecognition.h"

MainPanel::MainPanel(wxFrame* parent):wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
{
	// Create a sizer that will lay out child windows vertically
	// one above each other
	auto sizer = new wxBoxSizer(wxVERTICAL);

	// Create the view class object as a child of MainFrame
	mFaceRecognitionView = new FaceRecognitionView(this);
	mFaceDetectionView = new FaceDetectionView(this);

	sizer->Add(mFaceRecognitionView, 3, wxEXPAND | wxALL);
	sizer->Add(mFaceDetectionView, 2, wxEXPAND | wxALL);

	auto faceRecognition = std::make_shared<FaceRecognition>();

	mFaceDetectionView->SetFaceRecognition(faceRecognition);
	mFaceRecognitionView->SetFaceRecognition(faceRecognition);

	// Set the sizer for this frame
	this->SetSizer(sizer);

	// Layout (place) the child windows.
	this->Layout();
}
