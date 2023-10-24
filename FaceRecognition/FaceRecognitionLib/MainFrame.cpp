
#include "pch.h"
#include "MainFrame.h"
#include "FaceRecognitionView.h"
#include "FaceDetectionView.h"
#include "ids.h"
#include "FaceRecognition.h"
/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
	Create(nullptr, wxID_ANY, L"Face Recognition", wxDefaultPosition, wxSize(1000, 800));
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
	// Create a sizer that will lay out child windows vertically
	// one above each other
	auto sizer = new wxBoxSizer(wxVERTICAL);

	// Create the view class object as a child of MainFrame
	mFaceRecognitionView = new FaceRecognitionView(this);
	mFaceDetectionView = new FaceDetectionView(this);

	sizer->Add(mFaceRecognitionView, 1, wxEXPAND | wxALL);
	sizer->Add(mFaceDetectionView, 0, wxEXPAND | wxALL);

	auto faceRecognition = std::make_shared<FaceRecognition>();

	mFaceDetectionView->SetFaceRecognition(faceRecognition);
	mFaceRecognitionView->SetFaceRecognition(faceRecognition);

	// Set the sizer for this frame
	SetSizer(sizer);

	// Layout (place) the child windows.
	Layout();

	auto menuBar = new wxMenuBar();

	auto fileMenu = new wxMenu();
	auto helpMenu = new wxMenu();

	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
	fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save aquarium as...");
	fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open aquarium file...");

	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	SetMenuBar(menuBar);
	CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(L"Welcome to the Face REcognition!",
		L"About Face Recognition",
		wxOK,
		this);
}
