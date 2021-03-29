#pragma once
#include "FrameMain.h"
#include <wx/wx.h>

class Dashboard : public wxFrame
{
public:
	Dashboard(FrameMain* parent);

private:
	void BuildGUI();

	void OnClose(wxCloseEvent& event);
	void OnLogoutBtn(wxCommandEvent& event);

private:
	FrameMain* mParent;

	wxDECLARE_EVENT_TABLE();
};

