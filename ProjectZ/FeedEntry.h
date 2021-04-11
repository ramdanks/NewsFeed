#pragma once
#include "wx/wx.h"
#include <wx/stc/stc.h>
#include <unordered_map>

class FeedEntry : public wxPanel
{
public:
	FeedEntry(wxWindow* parent);

private:
	void OnFlagBtn(wxCommandEvent& event);
	void OnPostBtn(wxCommandEvent& event);
	void BuildGUI();

	wxDECLARE_EVENT_TABLE();

	wxChoice* mCombo;
	wxStyledTextCtrl* mSTC;
	std::unordered_map<int, wxString> mFlags;
};
