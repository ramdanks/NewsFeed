#pragma once
#include <wx/wx.h>
#include <wx/combobox.h>
#include <wx/hyperlink.h>
#include <wx/aui/auibook.h>
#include "DatePicker.h"

#define WND_LOGIN_SIZE    wxSize(330, 400)
#define WND_SIGNUP_SIZE   wxSize(330, 555)

class FrameMain : public wxFrame
{
public:
	enum LandingMode { LOGIN, SIGNUP };

	FrameMain(const wxString& title = L"Main",
			  const wxPoint& pos = wxDefaultPosition);

	LandingMode GetMode() const;
	void SetMode(LandingMode mode);

private:
	struct LoginCtrl
	{
		wxStaticText* Warn;
		wxTextCtrl* UserCtrl, *PassCtrl;
	};
	struct RegisterCtrl
	{
		wxString Date;
		wxStaticText* Warn;
		wxCheckBox* Terms;
		wxButton* DobBtn;
		wxTextCtrl* UserCtrl, *PassCtrl, *PassConfirmCtrl, *EmailCtrl;
	};

	void BuildGUI();
	void Warn(const wxString& msg, bool ok = false);

	void OnClose(wxCloseEvent& event);
	void OnLoginBtn(wxCommandEvent& event);
	void OnSignupBtn(wxCommandEvent& event);
	void OnDateBtn(wxCommandEvent& event);
	void OnForgotLink(wxHyperlinkEvent& event);
	void OnSignupLink(wxHyperlinkEvent& event);
	void OnLoginLink(wxHyperlinkEvent& event);
	void OnPageChanged(wxAuiNotebookEvent& event);

private:
	wxAuiNotebook* mNotebook;
	LoginCtrl mLog;
	RegisterCtrl mReg;
	LandingMode mMode;

	wxDECLARE_EVENT_TABLE();
};