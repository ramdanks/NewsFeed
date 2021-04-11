#include "Dashboard.h"
#include "SystemBar.h"
#include "UserPanel.h"
#include "Image.h"
#include "FeedTitle.h"
#include "Theme.h"
#include "ProfileWindow.h"
#include "Feed.h"
#include "FeedWindow.h"
#include "Id.h"

wxBEGIN_EVENT_TABLE(Dashboard, wxFrame)
EVT_CLOSE(Dashboard::OnClose)
EVT_BUTTON(ID_LOGOUT_BTN, Dashboard::OnLogoutBtn)
wxEND_EVENT_TABLE()

Dashboard::Dashboard(wxWindow* parent)
	: wxFrame(nullptr, wxID_ANY, "Dashboard", wxDefaultPosition, wxSize(1280, 720)),
	mParent(parent)
{
	Image::Fetch();
	BuildGUI();
	Center();
	this->SetIcon(wxICON(ICO_LOGO));
}

void Dashboard::BuildGUI()
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	auto* navSizer = new wxBoxSizer(wxVERTICAL);
	auto* cntSizer = new wxBoxSizer(wxVERTICAL);

	auto* cntPanel = new wxPanel(this);
	auto* navPanel = new wxPanel(this);

	auto* searchSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* searchImg = new wxButton(navPanel, -1, "", wxPoint(0,0), wxSize(30,30), wxNO_BORDER);
	auto* searchEntry = new wxTextCtrl(navPanel, -1, wxEmptyString, wxPoint(0,0), wxSize(180,30), wxNO_BORDER);
	searchEntry->SetHint("Search for messages in chats");

	auto* userPanel = new UserPanel(navPanel);
	auto* wndFriend = new ProfileWindow(navPanel);
	FeedTitle::Init(cntPanel, wxSize(0,50), "All");
	auto* wndFeed = new FeedWindow(cntPanel);

	sFeed feed = {0, "Alert", "10/10/2020", "Hello apa kabar semuanya, Hello apa kabar semuanya!"};
	sProfile profile = {"buzzlyear", "Buzz Lightyear", "To Infinity and Beyond!",
						Image::GetBitmap(PROFILE_IMG)};
	for (int i = 0; i < 50; i++)
	{
		wndFriend->Add(profile);
		wndFeed->Add(feed);
		feed.id++;
	}

	searchSizer->Add(searchImg, 0, wxLEFT, 15);
	searchSizer->Add(searchEntry, 1, wxEXPAND | wxRIGHT, 15);

	navSizer->AddSpacer(10);
	navSizer->Add(searchSizer, 0, wxEXPAND);
	navSizer->AddSpacer(10);
	navSizer->Add(wndFriend, 1, wxEXPAND);
	navSizer->Add(userPanel, 0, wxEXPAND);
	navPanel->SetSizer(navSizer);

	cntSizer->Add(FeedTitle::Get(), 0, wxEXPAND);
	cntSizer->Add(wndFeed, 1, wxEXPAND);
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
