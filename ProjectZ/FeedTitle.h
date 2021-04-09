#pragma once
#include <wx/wx.h>

class FeedTitle
{
private:
	FeedTitle() {}

public:
	static void Init(wxWindow* parent, wxSize size, wxString title = "");
	static void SetTitle(wxString title);
	static wxString GetTitle();
	static wxPanel* Get();

private:
	static wxPanel* mPanel;
	static wxStaticText* mTitle;

	wxDECLARE_EVENT_TABLE();
};

