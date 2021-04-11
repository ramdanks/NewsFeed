#pragma once
#include <wx/wx.h>

class FlagSetting : public wxDialog
{
public:
	FlagSetting(wxWindow* parent, const std::vector<wxString>& flags);

	wxArrayString GetFlagList();

private:
	void OnAddFlags(wxCommandEvent& event);
	void OnRemoveFlags(wxCommandEvent& event);
	void OnListBox(wxCommandEvent& event);
	void BuildGUI(const std::vector<wxString>& flags);

	wxTextCtrl* mAddEntry, * mRemoveEntry;
	wxListBox* mListbox;

	wxDECLARE_EVENT_TABLE();
};

