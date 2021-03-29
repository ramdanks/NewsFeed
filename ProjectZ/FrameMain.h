#pragma once
#include <wx/wx.h>
#include <wx/hyperlink.h>

class FrameMain : public wxFrame
{
public:
	FrameMain(const wxString& title = L"Main",
			  const wxPoint& pos = wxDefaultPosition,
			  const wxSize& size = wxDefaultSize);

	void Quit();

private:
	void BuildGUI();

	void OnClose(wxCloseEvent& event);
	void OnLoginBtn(wxCommandEvent& event);
	void OnForgotLink(wxHyperlinkEvent& event);
	void OnSignupLink(wxHyperlinkEvent& event);

private:
	wxTextCtrl* mUserCtrl;
	wxTextCtrl* mPassCtrl;
	wxStaticText* mWarn;

	wxDECLARE_EVENT_TABLE();
};