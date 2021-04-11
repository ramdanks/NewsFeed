#include "Dashboard.h"
#include "SystemBar.h"
#include "UserPanel.h"
#include "Image.h"
#include "FeedTitle.h"
#include "Theme.h"
#include "Feed.h"
#include "Id.h"
#include "DBRequest.h"
#include "ProfileDialog.h"
#include "SettingDialog.h"

#define STR_SET_LOGOUT        "Logout"
#define STR_SET_BIO           "Set Bio"
#define STR_SET_DISPLAYNAME   "Set Displayname"

wxDEFINE_EVENT(EVT_PW_PRESS, wxCommandEvent);
wxDEFINE_EVENT(EVT_PW_IMG, wxCommandEvent);
wxDEFINE_EVENT(EVT_UP_IMG, wxCommandEvent);
wxDEFINE_EVENT(EVT_UP_SETTING, wxCommandEvent);
wxDEFINE_EVENT(EVT_FE_POST, wxCommandEvent);
wxDEFINE_EVENT(EVT_PD_FOLLOW, wxCommandEvent);
wxDEFINE_EVENT(EVT_PD_UNFOLLOW, wxCommandEvent);

wxBEGIN_EVENT_TABLE(Dashboard, wxFrame)
EVT_CLOSE(Dashboard::OnClose)
EVT_BUTTON(ID_LOGOUT_BTN, Dashboard::OnLogoutBtn)
EVT_BUTTON(ID_ADDFRIEND_BTN, Dashboard::OnAddFriend)
EVT_COMMAND(wxID_ANY, EVT_PW_PRESS, Dashboard::OnFeedChange)
EVT_COMMAND(wxID_ANY, EVT_PW_IMG, Dashboard::OnProfileDialog)
EVT_COMMAND(wxID_ANY, EVT_UP_IMG, Dashboard::OnProfileDialog)
EVT_COMMAND(wxID_ANY, EVT_UP_SETTING, Dashboard::OnSettingBtn)
EVT_COMMAND(wxID_ANY, EVT_FE_POST, Dashboard::OnFeedPost)
EVT_COMMAND(wxID_ANY, EVT_PD_FOLLOW, Dashboard::OnFollowProfile)
EVT_COMMAND(wxID_ANY, EVT_PD_UNFOLLOW, Dashboard::OnUnfollowProfile)
wxEND_EVENT_TABLE()

Dashboard::Dashboard(wxWindow* parent, const wxString& username)
	: wxFrame(nullptr, wxID_ANY, "Dashboard", wxDefaultPosition, wxSize(1280, 720)),
	mParent(parent)
{
	Image::Fetch();

	mProfile = DBRequest::GetProfile(username.ToStdString());
	mProfile.picture = Image::GetBitmap(PROFILE_IMG);

	BuildGUI();
	InitProfile();
	InitFlag();
	ChangeFeed(mProfile.username);

	Center();
	this->SetIcon(wxICON(ICO_LOGO));
}

void Dashboard::ChangeFeed(const wxString& username)
{
	FeedTitle::SetTitle(username);
	if (mFeedOwner == username) return;

	username == UserPanel::GetUser().username ? mFeedEntry->Show() : mFeedEntry->Hide();
	mFeedOwner = username;

	mFeedWnd->Clear();

	auto feeds = DBRequest::GetFeeds(username.ToStdString());
	for (const auto& f : feeds)
		mFeedWnd->Add(f);
}

void Dashboard::InitProfile()
{
	auto vector = DBRequest::GetFollowing(mProfile.username.ToStdString());
	for (const std::string& i : vector)
	{
		sProfile p = DBRequest::GetProfile(i);
		p.picture = Image::GetBitmap(PROFILE_IMG);
		p.status = FOLLOWED;
		mProfileWnd->Add(p);
	}
}

void Dashboard::InitFlag()
{
	auto vector = DBRequest::GetFlag(mProfile.username.ToStdString());
	for (const auto& e : vector)
		mFeedEntry->AddFlag(e);
}

void Dashboard::BuildGUI()
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	auto* navSizer = new wxBoxSizer(wxVERTICAL);
	auto* cntSizer = new wxBoxSizer(wxVERTICAL);

	auto* cntPanel = new wxPanel(this);
	auto* navPanel = new wxPanel(this);

	auto* searchSizer = new wxBoxSizer(wxHORIZONTAL);

	auto addfimg = Image::GetImage(ADDFRIEND_PNG);
	addfimg.Rescale(18, 18);

	auto* addfriend = new wxBitmapButton(navPanel, ID_ADDFRIEND_BTN, wxBitmap(addfimg));
	auto* searchEntry = new wxTextCtrl(navPanel, -1, wxEmptyString, wxPoint(0,0), wxSize(100,20), wxNO_BORDER);
	searchEntry->SetHint("Search for Friends");
	searchEntry->SetFont(FONT_SEARCH_NAV);

	UserPanel::Init(navPanel, mProfile);
	mProfileWnd = new ProfileWindow(navPanel);
	FeedTitle::Init(cntPanel, wxSize(0,46), mProfile.username);
	mFeedWnd = new FeedWindow(cntPanel);

	mFeedEntry = new FeedEntry(cntPanel);

	searchSizer->Add(addfriend, 0, wxLEFT, 15);
	searchSizer->Add(searchEntry, 1, wxCENTER | wxRIGHT, 15);

	navSizer->AddSpacer(10);
	navSizer->Add(searchSizer, 0, wxEXPAND);
	navSizer->AddSpacer(10);
	navSizer->Add(mProfileWnd, 1, wxEXPAND);
	navSizer->Add(UserPanel::Get(), 0, wxEXPAND);
	navPanel->SetSizer(navSizer);
	navSizer->SetMinSize(wxSize(200, 0));

	cntSizer->Add(FeedTitle::Get(), 0, wxEXPAND);
	cntSizer->Add(mFeedWnd, 1, wxEXPAND);
	cntSizer->Add(mFeedEntry, 0, wxEXPAND);
	cntPanel->SetSizer(cntSizer);

	sizer->Add(navPanel, 0, wxEXPAND);
	sizer->Add(cntPanel, 1, wxEXPAND);

	this->SetSizer(sizer);
	this->SetMinSize(wxSize(400, 400));
	this->Layout();

	Theme::SetWindow(cntPanel, CLR_CHAT_BACK, CLR_CHAT_FORE);
	Theme::SetWindow(navPanel, CLR_NAV_BACK, CLR_NAV_FORE);
	Theme::SetWindow(searchEntry, CLR_ENTRY_BACK, CLR_ENTRY_FORE);
}

void Dashboard::OnClose(wxCloseEvent& event)
{
	this->Hide();
	this->Destroy();
	if (mParent)
		mParent->Destroy();
}

void Dashboard::OnLogoutBtn(wxCommandEvent& event)
{
	this->Hide();
	this->Destroy();
	if (mParent)
		mParent->Show();
}

void Dashboard::OnAddFriend(wxCommandEvent& event)
{
	wxTextEntryDialog add(this, "Insert username:", "Add Friend");
	if (add.ShowModal() == wxID_OK)
	{
		sProfile p;
		wxString receiver = add.GetValue();
		if (receiver == mProfile.username)
		{
			p = mProfile;
		}
		else if (mProfileWnd->IsExist(receiver))
		{
			p = mProfileWnd->GetProfile(receiver);
		}
		else if (DBRequest::UserExist(receiver.ToStdString()))
		{
			p = DBRequest::GetProfile(receiver.ToStdString());
			p.picture = Image::GetBitmap(PROFILE_IMG);
			p.status = NONFOLLOWED;
		}
		else
		{
			wxMessageBox("Can't find that username!", "Not Found");
			return;
		}
		ProfileDialog pd(p, this);
		pd.ShowModal();
	}
}

void Dashboard::OnFeedChange(wxCommandEvent& event)
{
	this->Freeze();
	auto username = event.GetString();
	ChangeFeed(username);
	this->Thaw();
}

void Dashboard::OnFeedPost(wxCommandEvent& event)
{
	auto* p = (sFeed*) event.GetClientData();
	mFeedWnd->Add(*p);
	delete p;
}

void Dashboard::OnProfileDialog(wxCommandEvent& event)
{
	auto* info = (sProfile*) event.GetClientData();
	ProfileDialog pd(*info, this);
	if (pd.ShowModal() == FEED)
		ChangeFeed(info->username);
}

void Dashboard::OnFollowProfile(wxCommandEvent& event)
{
	sProfile p = DBRequest::GetProfile(event.GetString().ToStdString());
	p.picture = Image::GetBitmap(PROFILE_IMG);
	p.status = FOLLOWED;
	mProfileWnd->Add(p);
}

void Dashboard::OnUnfollowProfile(wxCommandEvent& event)
{
	mProfileWnd->Remove(event.GetString());
	mProfileWnd->Refresh();
}

void Dashboard::OnSettingBtn(wxCommandEvent& event)
{
	SettingDialog sd(this);
	if (sd.ShowModal() == MODAL_LOGOUT)
	{
		this->Hide();
		this->Destroy();
		if (mParent)
			mParent->Show();
	}
}
