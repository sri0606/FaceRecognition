#pragma once

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:

public:
	void Initialize();

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
