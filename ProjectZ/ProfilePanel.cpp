#include "ProfilePanel.h"
#include "ProfileDialog.h"
#include "Image.h"
#include "Theme.h"
#include "FeedTitle.h"

BEGIN_EVENT_TABLE(ProfilePanel, wxPanel)
EVT_MOTION(ProfilePanel::OnMouseMove)
EVT_LEFT_DOWN(ProfilePanel::OnMouseLPress)
EVT_LEFT_UP(ProfilePanel::OnMouseLRelease)
EVT_RIGHT_DOWN(ProfilePanel::OnMouseRClick)
EVT_LEAVE_WINDOW(ProfilePanel::OnMouseLeave)
EVT_ENTER_WINDOW(ProfilePanel::OnMouseEnter)
END_EVENT_TABLE()

#define PICTURE_WIDTH  30
#define PICTURE_HEIGHT 30

ProfilePanel::ProfilePanel(const sProfile& info, wxWindow* parent, const wxWindowID& id, const wxPoint& point, const wxSize& size)
	: wxPanel(parent, id, point, size),
	mInfo(info),
	mFocus(false)
{
	BuildGUI();
}

void ProfilePanel::SetInfo(const sProfile& info)
{
	mInfo = info;
	Image::SetBitmapScale(mInfo.picture, PICTURE_WIDTH, PICTURE_HEIGHT);

	mBio->SetLabel(mInfo.bio);
	mName->SetLabel(mInfo.name);
	mPicture->SetBitmap(mInfo.picture);
}

void ProfilePanel::BuildGUI()
{
	Theme::SetWindow(this, CLR_FRIEND_IDLE_BACK, CLR_FRIEND_IDLE_FORE);	
	Image::SetBitmapScale(mInfo.picture, PICTURE_WIDTH, PICTURE_HEIGHT);

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* sizerText = new wxBoxSizer(wxVERTICAL);
	mPicture = new wxStaticBitmap(this, -1, mInfo.picture);
	mName = new wxStaticText(this, -1, mInfo.name);
	mBio = new wxStaticText(this, -1, mInfo.bio);
	mName->SetFont(FONT_FRIEND_NAME);
	mBio->SetFont(FONT_FRIEND_BIO);
	mBio->SetForegroundColour(CLR_FRIEND_BIO);

	sizerText->Add(mName, 0);
	sizerText->AddSpacer(3);
	sizerText->Add(mBio, 0);

	sizer->Add(mPicture, 0, wxCENTER | wxLEFT, 10);
	sizer->Add(sizerText, 0, wxCENTER | wxLEFT | wxRIGHT, 10);
	this->SetSizer(sizer);
}

void ProfilePanel::OnMouseMove(wxMouseEvent& event)
{
}

void ProfilePanel::OnMouseLPress(wxMouseEvent& event)
{
	auto pos = event.GetPosition();
	auto ppos = mPicture->GetPosition();
	auto psize = mPicture->GetSize();

	if (pos.x >= ppos.x && pos.y >= ppos.y &&
		pos.x <= ppos.x + psize.x && pos.y <= ppos.y + psize.y)
	{
		ProfileDialog d(mInfo, this);
		d.ShowModal();
	}
	else
	{
		FeedTitle::SetTitle(mInfo.name);
	}
}

void ProfilePanel::OnMouseLRelease(wxMouseEvent& event)
{
}

void ProfilePanel::OnMouseRClick(wxMouseEvent& event)
{
}

void ProfilePanel::OnMouseEnter(wxMouseEvent& event)
{
	CaptureMouse();
	mFocus = true;
	Theme::SetWindow(this, CLR_FRIEND_FOCUS_BACK, CLR_FRIEND_FOCUS_FORE);
	this->Refresh();
}

void ProfilePanel::OnMouseLeave(wxMouseEvent& event)
{
	ReleaseMouse();
	mFocus = false;
	Theme::SetWindow(this, CLR_FRIEND_IDLE_BACK, CLR_FRIEND_IDLE_FORE);
	this->Refresh();
}
