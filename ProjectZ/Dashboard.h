#pragma once
#include <wx/wx.h>

class Dashboard : public wxFrame
{
public:
	Dashboard(wxWindow* parent);

private:
	void BuildGUI();

	void OnClose(wxCloseEvent& event);
	void OnLogoutBtn(wxCommandEvent& event);

private:
	wxWindow* mParent;

	wxDECLARE_EVENT_TABLE();
};

