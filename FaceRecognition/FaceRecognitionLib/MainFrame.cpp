
#include "pch.h"
#include "MainFrame.h"
//#include "AquariumView.h"
//#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
	Create(nullptr, wxID_ANY, L"Aquarium", wxDefaultPosition, wxSize(1000, 800));
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
	// Create a sizer that will lay out child windows vertically
	// one above each other
	auto sizer = new wxBoxSizer(wxVERTICAL);

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
	wxMessageBox(L"Welcome to the Aquarium!",
		L"About Aquarium",
		wxOK,
		this);
}
