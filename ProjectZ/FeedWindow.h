#pragma once
#include <wx/wx.h>
#include <unordered_map>
#include "Feed.h"
#include "FeedPanel.h"

class FeedWindow : public wxScrolledWindow
{
public:
	FeedWindow(wxWindow* parent);

	bool Add(const sFeed& feed);
	bool Remove(int id);
	bool Remove(const sFeed& feed);
	bool IsExist(int id);
	bool IsExist(const sFeed& feed);

private:
	void BuildGUI();

	wxSizer* mSizer;
	std::unordered_map<int, FeedPanel*> mFeeds;
};