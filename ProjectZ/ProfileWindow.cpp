#include "ProfileWindow.h"
#include "ProfilePanel.h"
#include "Profile.h"
#include "Theme.h"
#include "Image.h"
#include "Dashboard.h"
#include "Id.h"

wxDEFINE_EVENT(EVT_PP_PRESS, wxCommandEvent);
wxDEFINE_EVENT(EVT_PP_IMG, wxCommandEvent);

BEGIN_EVENT_TABLE(ProfileWindow, wxScrolledWindow)
EVT_COMMAND(wxID_ANY, EVT_PP_PRESS, ProfileWindow::OnProfileClick)
EVT_COMMAND(wxID_ANY, EVT_PP_IMG, ProfileWindow::OnProfileImg)
END_EVENT_TABLE()

ProfileWindow::ProfileWindow(wxWindow* parent)
	: wxScrolledWindow(parent, wxID_ANY),
	mParent(parent)
{
	BuildGUI();
	this->SetCursor(wxCURSOR_HAND);
}

bool ProfileWindow::Add(const sProfile& profile)
{
	if (IsExist(profile))
		return false;
	auto* profilep = new ProfilePanel(profile, this, -1, wxPoint(0, 0), wxSize(10, 50));
	mProfiles[profile.username] = {mSizer->GetItemCount(), profilep};
	mSizer->Add(profilep, 0, wxEXPAND);
	mSizer->Layout();
	return true;
}

bool ProfileWindow::Remove(const sProfile& profile)
{
	return Remove(profile.username);
}

bool ProfileWindow::Remove(const wxString& username)
{
	auto it = mProfiles.find(username);
	if (it == mProfiles.end()) return false;
	mSizer->Remove(it->second.sizerIndex);
	it->second.wnd->Destroy();
	mProfiles.erase(username);
	mSizer->Layout();
	return true;
}

bool ProfileWindow::IsExist(const sProfile& profile)
{
	return IsExist(profile.username);
}

bool ProfileWindow::IsExist(const wxString& username)
{
	auto it = mProfiles.find(username);
	return it != mProfiles.end();
}

sProfile ProfileWindow::GetProfile(const wxString& username)
{
	auto it = mProfiles.find(username);
	if (it == mProfiles.end())
		return sProfile();
	return it->second.p;
}

void ProfileWindow::OnProfileImg(wxCommandEvent& event)
{
	wxCommandEvent currE(EVT_PW_IMG);
	currE.SetClientData(event.GetClientData());
	wxPostEvent(mParent, currE);
}

void ProfileWindow::OnProfileClick(wxCommandEvent& event)
{
	wxCommandEvent currE(EVT_PW_PRESS);
	currE.SetString(event.GetString());
	wxPostEvent(mParent, currE);
}

void ProfileWindow::BuildGUI()
{
	constexpr int height = 50;
	constexpr int width = 100;
	constexpr int size = 30;

	constexpr int scrollUnitX = width / 10;
	constexpr int scrollUnitY = height / 10;

	constexpr int scaleUnitX = width / scrollUnitX;
	constexpr int scaleUnitY = size * height / scrollUnitY;

	SetScrollbars(scrollUnitX, scrollUnitY,
				  scaleUnitX, scaleUnitY,
				  0, 0);

	mSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mSizer);
}
