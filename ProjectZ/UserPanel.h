#pragma once
#include <wx/wx.h>
#include "Profile.h"

wxDECLARE_EVENT(EVT_UP_IMG, wxCommandEvent);
wxDECLARE_EVENT(EVT_UP_SETTING, wxCommandEvent);

#define USER_PICTURE_WIDTH  35
#define USER_PICTURE_HEIGHT 35

class UserPanel
{
private:
	UserPanel() {}
	

public:
	static void Init(wxWindow* parent, sProfile&& profile);
	static void Init(wxWindow* parent, const sProfile& profile);

	static wxPanel* Get();
	static sProfile GetUser();
	static void SetDisplayname(const wxString& name);
	static void SetBio(const wxString& bio);

private:
	static void OnSettingBtn(wxCommandEvent& event);
	static void OnPictureBtn(wxCommandEvent& event);
	static void BuildGUI();

	static wxStaticText* sName, * sBio;
	static wxPanel* sPanel;
	static sProfile sUser;

	wxDECLARE_EVENT_TABLE();
};