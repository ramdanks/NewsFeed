#pragma once
#include <wx/wx.h>

#define MODAL_LOGOUT 10

class SettingDialog : public wxDialog
{
public:
	SettingDialog(wxWindow* parent);

private:
	void OnLogoutBtn(wxCommandEvent& event);
	void OnSetBioBtn(wxCommandEvent& event);
	void OnSetDisplaynameBtn(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

