#include "ProfileWindow.h"
#include "ProfilePanel.h"
#include "Profile.h"
#include "Theme.h"
#include "Image.h"

ProfileWindow::ProfileWindow(wxWindow* parent)
	: wxScrolledWindow(parent, wxID_ANY)
{
	BuildGUI();
	this->SetCursor(wxCURSOR_HAND);
}

bool ProfileWindow::Add(const sProfile& profile)
{
	if (IsExist(profile))
		return false;
	auto* profilep = new ProfilePanel(profile, this, -1, wxPoint(0, 0), wxSize(0, 50));
	mProfiles[profile.username] = profile;
	mSizer->Add(profilep, 0, wxEXPAND);
	return true;
}

bool ProfileWindow::Remove(const sProfile& profile)
{
	mProfiles.erase(profile.username);
	return true;
}

bool ProfileWindow::Remove(const wxString& username)
{
	mProfiles.erase(username);
	return true;
}

bool ProfileWindow::IsExist(const sProfile& profile)
{
	auto it = mProfiles.find(profile.username);
	return it != mProfiles.end();
}

bool ProfileWindow::IsExist(const wxString& username)
{
	auto it = mProfiles.find(username);
	return it != mProfiles.end();
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
