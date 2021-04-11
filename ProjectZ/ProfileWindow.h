#pragma once
#include <wx/wx.h>
#include <unordered_map>
#include "Profile.h"

wxDECLARE_EVENT(EVT_PW_PRESS, wxCommandEvent);
wxDECLARE_EVENT(EVT_PW_IMG, wxCommandEvent);

class ProfileWindow : public wxScrolledWindow
{
	struct sWndData { size_t sizerIndex; wxWindow* wnd; sProfile p; };
public:
	ProfileWindow(wxWindow* parent);

	bool Add(const sProfile& profile);
	bool Remove(const sProfile& profile);
	bool Remove(const wxString& username);
	bool IsExist(const sProfile& profile);
	bool IsExist(const wxString& username);
	sProfile GetProfile(const wxString& username);
	
private:
	void OnProfileImg(wxCommandEvent& event);
	void OnProfileClick(wxCommandEvent& event);
	void BuildGUI();

	wxWindow* mParent;
	wxSizer* mSizer;
	std::unordered_map<wxString, sWndData> mProfiles;
	
	wxDECLARE_EVENT_TABLE();
};

