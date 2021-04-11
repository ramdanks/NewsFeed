#pragma once
#include <wx/wx.h>
#include "ProfileWindow.h"
#include "FeedEntry.h"
#include "FeedWindow.h"

class Dashboard : public wxFrame
{
public:
	Dashboard(wxWindow* parent, const wxString& username);

	void ChangeFeed(const wxString& username);

private:
	void OnClose(wxCloseEvent& event);
	void OnLogoutBtn(wxCommandEvent& event);
	void OnAddFriend(wxCommandEvent& event);
	void OnFeedChange(wxCommandEvent& event);
	void OnFeedPost(wxCommandEvent& event);
	void OnProfileDialog(wxCommandEvent& event);
	void OnFollowProfile(wxCommandEvent& event);
	void OnUnfollowProfile(wxCommandEvent& event);
	void OnSettingBtn(wxCommandEvent& event);

	void InitProfile();
	void InitFlag();
	void BuildGUI();

private:
	sProfile mProfile;
	wxWindow* mParent;
	ProfileWindow* mProfileWnd;
	FeedEntry* mFeedEntry;
	FeedWindow* mFeedWnd;
	wxString mFeedOwner;

	wxDECLARE_EVENT_TABLE();
};

