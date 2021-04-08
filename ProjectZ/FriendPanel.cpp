#include "FriendPanel.h"
#include "Image.h"
#include "Theme.h"

BEGIN_EVENT_TABLE(FriendPanel, wxPanel)
EVT_MOTION(FriendPanel::OnMouseMove)
EVT_LEFT_DOWN(FriendPanel::OnMouseLPress)
EVT_LEFT_UP(FriendPanel::OnMouseLRelease)
EVT_RIGHT_DOWN(FriendPanel::OnMouseRClick)
EVT_LEAVE_WINDOW(FriendPanel::OnMouseLeave)
EVT_ENTER_WINDOW(FriendPanel::OnMouseEnter)
END_EVENT_TABLE()

#define PICTURE_WIDTH  30
#define PICTURE_HEIGHT 30

FriendPanel::FriendPanel(const sFriend& info, wxWindow* parent, const wxWindowID& id, const wxPoint& point, const wxSize& size)
	: wxPanel(parent, id, point, size),
	mInfo(info),
	mFocus(false)
{
	BuildGUI();
}

void FriendPanel::SetInfo(const sFriend& info)
{
	mInfo = info;
	Image::SetBitmapScale(mInfo.picture, PICTURE_WIDTH, PICTURE_HEIGHT);

	mBio->SetLabel(mInfo.bio);
	mName->SetLabel(mInfo.name);
	mPicture->SetBitmap(mInfo.picture);
}

void FriendPanel::BuildGUI()
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

void FriendPanel::OnMouseMove(wxMouseEvent& event)
{
}

void FriendPanel::OnMouseLPress(wxMouseEvent& event)
{
	auto pos = event.GetPosition();
	auto ppos = mPicture->GetPosition();
	auto psize = mPicture->GetSize();

	if (pos.x >= ppos.x && pos.y >= ppos.y &&
		pos.x <= ppos.x + psize.x && pos.y <= ppos.y + psize.y)
	{
		wxDialog d(this, -1, mInfo.bio);
		if (d.ShowModal());
	}
}

void FriendPanel::OnMouseLRelease(wxMouseEvent& event)
{
}

void FriendPanel::OnMouseRClick(wxMouseEvent& event)
{
}

void FriendPanel::OnMouseEnter(wxMouseEvent& event)
{
	CaptureMouse();
	mFocus = true;
	Theme::SetWindow(this, CLR_FRIEND_FOCUS_BACK, CLR_FRIEND_FOCUS_FORE);
	this->Refresh();
}

void FriendPanel::OnMouseLeave(wxMouseEvent& event)
{
	ReleaseMouse();
	mFocus = false;
	Theme::SetWindow(this, CLR_FRIEND_IDLE_BACK, CLR_FRIEND_IDLE_FORE);
	this->Refresh();
}
