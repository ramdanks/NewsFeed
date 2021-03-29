#include "Dashboard.h"
#include "Id.h"

wxBEGIN_EVENT_TABLE(Dashboard, wxFrame)
EVT_CLOSE(Dashboard::OnClose)
EVT_BUTTON(ID_LOGOUT_BTN, Dashboard::OnLogoutBtn)
wxEND_EVENT_TABLE()

Dashboard::Dashboard(FrameMain* parent)
	: wxFrame(nullptr, wxID_ANY, "Dashboard"),
	mParent(parent)
{
	auto* logout = new wxButton(this, ID_LOGOUT_BTN, "Log Out");
}

void Dashboard::BuildGUI()
{

}

void Dashboard::OnClose(wxCloseEvent& event)
{
	mParent->Quit();
	this->Hide();
	this->Destroy();
}

void Dashboard::OnLogoutBtn(wxCommandEvent& event)
{
	this->Hide();
	this->Destroy();
	mParent->Show();
}
