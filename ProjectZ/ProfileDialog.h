#pragma once
#include <wx/wx.h>
#include "Profile.h"

wxDECLARE_EVENT(EVT_PD_FOLLOW, wxCommandEvent);
wxDECLARE_EVENT(EVT_PD_UNFOLLOW, wxCommandEvent);

enum PDRet { NONE, FEED };

class ProfileDialog : public wxDialog
{
public:
	ProfileDialog(const sProfile& info, wxWindow* parent);

private:
	void OnFollowBtn(wxCommandEvent& event);
	void OnFeedBtn(wxCommandEvent& event);

	wxButton* mButton;
	sPStatus mStatus;
	std::string mUsername;

	wxDECLARE_EVENT_TABLE();
};
