#pragma once
#include "wx/wx.h"
#include <wx/stc/stc.h>

wxDECLARE_EVENT(EVT_FE_POST, wxCommandEvent);

class FeedEntry : public wxPanel
{
public:
	FeedEntry(wxWindow* parent);

	void SetFlag(const wxArrayString& flags);
	void AddFlag(const wxString& flag);

private:
	void OnFlagBtn(wxCommandEvent& event);
	void OnPostBtn(wxCommandEvent& event);
	void BuildGUI();

	wxDECLARE_EVENT_TABLE();

	wxChoice* mCombo;
	wxStyledTextCtrl* mSTC;
	wxArrayString mFlags;
};
