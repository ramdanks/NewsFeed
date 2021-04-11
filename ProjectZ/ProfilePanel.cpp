#include "ProfilePanel.h"
#include "ProfileDialog.h"
#include "Image.h"
#include "Theme.h"
#include "FeedTitle.h"
#include "Dashboard.h"
#include "Id.h"

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
#define BIO_CHAR_LIMIT 40

ProfilePanel::ProfilePanel(const sProfile& info, wxWindow* parent, const wxWindowID& id, const wxPoint& point, const wxSize& size)
	: wxPanel(parent, id, point, size),
	mInfo(info),
	mFocus(false),
	mParent(parent)
{
	BuildGUI();
}

void ProfilePanel::SetInfo(const sProfile& info)
{
	mInfo = info;
	Image::SetBitmapScale(mInfo.picture, PICTURE_WIDTH, PICTURE_HEIGHT);

	mBio->SetLabel(mInfo.bio);
	mName->SetLabel(mInfo.displayname);
	mPicture->SetBitmap(mInfo.picture);
}

void ProfilePanel::BuildGUI()
{
	Theme::SetWindow(this, CLR_FRIEND_IDLE_BACK, CLR_FRIEND_IDLE_FORE);	
	Image::SetBitmapScale(mInfo.picture, PICTURE_WIDTH, PICTURE_HEIGHT);

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* sizerText = new wxBoxSizer(wxVERTICAL);
	mPicture = new wxStaticBitmap(this, -1, mInfo.picture);
	mName = new wxStaticText(this, -1, mInfo.displayname);


	if (mInfo.bio.length() <= BIO_CHAR_LIMIT)
		mBio = new wxStaticText(this, -1, mInfo.bio);
	else
	{
		wxString str = mInfo.bio;
		str.Truncate(BIO_CHAR_LIMIT);
		for (int i = BIO_CHAR_LIMIT - 4; i < BIO_CHAR_LIMIT; i++)
			str[i] = '\.';
		str[BIO_CHAR_LIMIT-1] = '\0';
		mBio = new wxStaticText(this, -1, str);
	}

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
		wxCommandEvent event(EVT_PP_IMG);
		event.SetClientData(&mInfo);
		wxPostEvent(mParent, event);
	}
	else
	{
		wxCommandEvent event(EVT_PP_PRESS);
		event.SetString(mInfo.username);
		wxPostEvent(mParent, event);
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