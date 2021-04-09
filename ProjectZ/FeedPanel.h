#pragma once
#include <wx/wx.h>
#include "Feed.h"

class FeedPanel : public wxPanel
{
public:
	FeedPanel(wxWindow* parent);
	FeedPanel(wxWindow* parent, const sFeed& feed);

	void SetDate(const wxString& date);
	void SetText(const wxString& text);
	void SetFlag(const wxString& flag);
	void SetFeed(const sFeed& feed);

private:
	void BuildGUI(const sFeed& feed);

	wxPanel* mHeader;
	wxStaticText* mFlag, * mDate;
	wxTextCtrl* mText;
};
