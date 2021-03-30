#pragma once
#include <wx/wx.h>
#include <wx/hyperlink.h>
#include <wx/aui/auibook.h>

#define WND_LOGIN_SIZE    wxSize(330, 400)
#define WND_SIGNUP_SIZE wxSize(330, 500)

class FrameMain : public wxFrame
{
public:
	enum LandingMode { LOGIN, SIGNUP };

	FrameMain(const wxString& title = L"Main",
			  const wxPoint& pos = wxDefaultPosition);

	LandingMode GetMode() const;
	void SetMode(LandingMode mode);
	void Quit();

private:
	struct LoginCtrl
	{
		wxTextCtrl* UserCtrl, *PassCtrl;
	};
	struct RegisterCtrl
	{
		wxTextCtrl* UserCtrl, *PassCtrl, *PassConfirmCtrl, *EmailCtrl;
	};

	void BuildGUI();

	void OnClose(wxCloseEvent& event);
	void OnLoginBtn(wxCommandEvent& event);
	void OnSignupBtn(wxCommandEvent& event);
	void OnForgotLink(wxHyperlinkEvent& event);
	void OnSignupLink(wxHyperlinkEvent& event);
	void OnLoginLink(wxHyperlinkEvent& event);
	void OnPageChanged(wxAuiNotebookEvent& event);

private:
	wxAuiNotebook* mNotebook;
	LoginCtrl mLog;
	RegisterCtrl mReg;
	LandingMode mMode;
	wxStaticText* mWarn;

	wxDECLARE_EVENT_TABLE();
};