#pragma once

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
	wxPanel* mLoadingPanel;
	wxPanel* mMainPanel;

public:
	void Initialize();

	void InitializeLoadingPanel();

	void OnLoadingTimer(wxTimerEvent& event);

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
