#include "ProfileDialog.h"
#include "Theme.h"
#include "DBRequest.h"
#include "UserPanel.h"
#include <wx/stc/stc.h>
#include "Id.h"

#define UNFOLLOW_LABEL   "Unfollow"
#define FOLLOW_LABEL     "Follow"

BEGIN_EVENT_TABLE(ProfileDialog, wxDialog)
EVT_BUTTON(ID_FOL_UNFOL_BTN, ProfileDialog::OnFollowBtn)
EVT_BUTTON(ID_FEED_BTN, ProfileDialog::OnFeedBtn)
END_EVENT_TABLE()

ProfileDialog::ProfileDialog(const sProfile& info, wxWindow* parent)
	: wxDialog(parent, -1, "Profile", wxDefaultPosition, wxSize(250, 300)),
	mStatus(info.status),
	mUsername(info.username.ToStdString())
{
	Theme::SetWindow(this, CLR_PROFILE_BACK, CLR_PROFILE_FORE);

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto* btnSizr = new wxBoxSizer(wxHORIZONTAL);

	auto img = info.picture.ConvertToImage();
	img.Rescale(100, 100);

	if (info.status != MYACCOUNT)
	{
		wxString label;
		if (info.status == FOLLOWED) label = UNFOLLOW_LABEL;
		else if (info.status == NONFOLLOWED) label = FOLLOW_LABEL;
		mButton = new wxButton(this, ID_FOL_UNFOL_BTN, label, wxPoint(0, 0), wxSize(0, 30));
		btnSizr->Add(mButton, 1, wxEXPAND);
	}
	auto* feed = new wxButton(this, ID_FEED_BTN, "Feed", wxPoint(0,0), wxSize(0, 30));
	btnSizr->Add(feed, 1, wxEXPAND);

	auto* name = new wxStaticText(this, -1, info.displayname);
	auto* bio = new wxStaticText(this, -1, info.bio);
	auto* pict = new wxStaticBitmap(this, -1, wxBitmap(img));

	bio->Wrap(200);
	name->SetFont(FONT_PROFILE);

	sizer->AddSpacer(10);
	sizer->Add(pict, 1, wxEXPAND);
	sizer->AddSpacer(10);
	sizer->Add(name, 0, wxCENTER | wxLEFT | wxRIGHT, 15);
	sizer->AddSpacer(10);
	sizer->Add(bio, 0, wxCENTER | wxLEFT | wxRIGHT, 15);
	sizer->AddSpacer(20);
	sizer->Add(btnSizr, 0, wxEXPAND);

	this->SetSizer(sizer);
	if (info.displayname.length() > 20)
		this->Fit();
}

void ProfileDialog::OnFollowBtn(wxCommandEvent& event)
{
	auto self = UserPanel::GetUser().username.ToStdString();
	try
	{
		wxCommandEvent postE;
		if (mStatus == FOLLOWED)
		{
			if (!DBRequest::Unfollow(self, mUsername))
				throw "Oops, cannot commit to the database!";
			mStatus = NONFOLLOWED;
			mButton->SetLabel(FOLLOW_LABEL);
			postE.SetEventType(EVT_PD_UNFOLLOW);
		}
		else if (mStatus == NONFOLLOWED)
		{
			if (!DBRequest::Follow(self, mUsername))
				throw "Oops, cannot commit to the database!";
			mStatus = FOLLOWED;
			mButton->SetLabel(UNFOLLOW_LABEL);
			postE.SetEventType(EVT_PD_FOLLOW);
		}
		postE.SetString(mUsername);
		wxPostEvent(GetParent(), postE);
	}
	catch (const char* msg)
	{
		wxMessageBox(msg, "Profile Request");
	}
}

void ProfileDialog::OnFeedBtn(wxCommandEvent& event)
{
	this->EndModal(FEED);
}
