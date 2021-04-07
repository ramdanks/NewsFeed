#include "Dashboard.h"
#include "SystemBar.h"
#include "Profile.h"
#include "Image.h"
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
}

void Dashboard::BuildGUI()
{
	const wxColour chatBack(20, 20, 20);
	const wxColour chatFore(240, 240, 240);
	const wxColour navBack(50, 50, 50);
	const wxColour navFore(240, 240, 240);

	auto SetTheme = [](wxWindow* wnd, const wxColour& back, const wxColour& fore)
	{
		wnd->SetBackgroundColour(back);
		wnd->SetForegroundColour(fore);
	};

	auto* sysSizer = new wxBoxSizer(wxVERTICAL);

	auto* sysbar = new SystemBar(this);

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* chatPanel = new wxPanel(this);
	auto* navPanel = new wxPanel(this);

	SetTheme(chatPanel, chatBack, chatFore);
	SetTheme(navPanel, navBack, navFore);
	SetTheme(sysbar, navBack, navFore);

	auto* navSizer = new wxBoxSizer(wxVERTICAL);

	auto* searchSizer = new wxBoxSizer(wxHORIZONTAL);
	auto* searchImg = new wxButton(navPanel, -1);
	auto* searchEntry = new wxTextCtrl(navPanel, -1, wxEmptyString, wxPoint(0,0), wxSize(180,30));
	searchEntry->SetHint("Search for messages in chats");

	auto* profile = new Profile(navPanel);

	searchSizer->Add(searchImg, 0, wxLEFT, 10);
	searchSizer->Add(searchEntry, 0, wxEXPAND | wxRIGHT, 10);

	navSizer->Add(searchSizer);
	navSizer->AddStretchSpacer();
	navSizer->Add(profile);
	navPanel->SetSizer(navSizer);

	//auto* logout = new wxButton(navPanel, ID_LOGOUT_BTN, "Log Out");

	sizer->Add(navPanel, 0, wxEXPAND);
	sizer->Add(chatPanel, 1, wxEXPAND);
	
	sysSizer->Add(sysbar, 0, wxEXPAND);
	sysSizer->Add(sizer, 1, wxEXPAND);

	this->SetSizer(sysSizer);
	sysSizer->SetSizeHints(this);
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
