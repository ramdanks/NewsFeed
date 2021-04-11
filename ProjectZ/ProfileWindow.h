#pragma once
#include <wx/wx.h>
#include <unordered_map>
#include "Profile.h"

class ProfileWindow : public wxScrolledWindow
{
public:
	ProfileWindow(wxWindow* parent);

	bool Add(const sProfile& profile);
	bool Remove(const sProfile& profile);
	bool Remove(const wxString& username);
	bool IsExist(const sProfile& profile);
	bool IsExist(const wxString& username);
	
private:
	void BuildGUI();

	wxSizer* mSizer;
	std::unordered_map<wxString, sProfile> mProfiles;
};

