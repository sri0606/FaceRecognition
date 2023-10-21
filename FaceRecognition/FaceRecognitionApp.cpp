
#include "FaceRecognitionApp.h"
#include <MainFrame.h>
#include "pch.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

/**
 * Initialize the application.
 * @return
 */
bool FaceRecognitionApp::OnInit()
{
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	if (!wxApp::OnInit())
		return false;

	// Add image type handlers
	wxInitAllImageHandlers();

	auto frame = new MainFrame();
	frame->Initialize();
	frame->Show(true);

	// Load the application icon from the icon file
	wxString iconFilePath = wxT("images/fac_rec_logo.ico");
	wxIcon appIcon;
	appIcon.CopyFromBitmap(wxBitmap(iconFilePath, wxBITMAP_TYPE_ICO));

	// Set the application icon
	SetTopWindow(frame); 
	frame->SetIcon(appIcon);

	return true;
}