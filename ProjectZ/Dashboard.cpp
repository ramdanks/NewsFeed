#include "Dashboard.h"
#include "SystemBar.h"
#include "Profile.h"
#include "Image.h"
#include "Theme.h"
#include "FriendWindow.h"
#include "Id.h"

wxBEGIN_EVENT_TABLE(Dashboard, wxFrame)
EVT_CLOSE(Dashboard::OnClose)
EVT_BUTTON(ID_LOGOUT_BTN, Dashboard::OnLogoutBtn)
wxEND_EVENT_TABLE()

constexpr long frameStyle = wxRESIZE_BORDER;

Dashboard::Dashboard(wxWindow* parent)
	: wxFrame(nullptr, wxID_ANY, "Dashboard", wxDefaultPosition,
			  wxSize(1280, 720), frameStyle),
	mParent(parent)
{
	Image::Fetch();
	BuildGUI();
	Center();
	this->SetIcon(wxICON(ICO_LOGO));
}

void Dashboard::BuildGUI()
{
	auto* sysSizer = new wxBoxSizer(wxVERTICAL);
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	auto* navSizer = new wxBoxSizer(wxVERTICAL);

	auto* sysbar = new SystemBar(this);
	auto* chatPanel = new wxPanel(this);
	auto* navPanel = new wxPanel(this);

	auto* searchSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* searchImg = new wxButton(navPanel, -1);
	auto* searchEntry = new wxTextCtrl(navPanel, -1, wxEmptyString, wxPoint(0,0), wxSize(180,30));
	searchEntry->SetHint("Search for messages in chats");

	auto* profile = new Profile(navPanel);
	auto* wndFriend = new FriendWindow(navPanel);

	searchSizer->Add(searchImg, 0, wxLEFT, 10);
	searchSizer->Add(searchEntry, 0, wxEXPAND | wxRIGHT, 10);

	navSizer->AddSpacer(10);
	navSizer->Add(searchSizer);
	navSizer->AddSpacer(10);
	navSizer->Add(wndFriend, 1, wxEXPAND);
	navSizer->Add(profile, 0, wxEXPAND);
	navPanel->SetSizer(navSizer);

	sizer->Add(navPanel, 0, wxEXPAND);
	sizer->Add(chatPanel, 1, wxEXPAND);
	
	sysSizer->Add(sysbar, 0, wxEXPAND);
	sysSizer->Add(sizer, 1, wxEXPAND);

	this->SetSizer(sysSizer);
	this->SetMinSize(wxSize(400, 400));
	this->Layout();

	Theme::SetWindow(chatPanel, CLR_CHAT_BACK, CLR_CHAT_FORE);
	Theme::SetWindow(navPanel, CLR_NAV_BACK, CLR_NAV_FORE);
	Theme::SetWindow(sysbar, CLR_SYSBAR_BACK, CLR_SYSBAR_FORE);
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
