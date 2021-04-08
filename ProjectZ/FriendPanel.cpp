#include "FriendPanel.h"
#include "wxImagePanel.h"
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

FriendPanel::FriendPanel(wxWindow* parent, const wxWindowID& id, const wxPoint& point, const wxSize& size)
	: wxPanel(parent, id, point, size),
	mFocus(false)
{
	BuildGUI();
}

void FriendPanel::SetInfo(const sFriend& info)
{
}

void FriendPanel::BuildGUI()
{
	Theme::SetWindow(this, CLR_FRIEND_IDLE_BACK, CLR_FRIEND_IDLE_FORE);	

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* sizerText = new wxBoxSizer(wxVERTICAL);
	mPicture = new wxStaticBitmap(this, -1, wxBitmap(Image::GetImageScale(PROFILE_IMG, 30, 30)));
	mName = new wxStaticText(this, -1, "Buzz Lightyear");
	mBio = new wxStaticText(this, -1, "To Infinity and Beyond!");
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
		wxDialog d(this, -1, "Wow");
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
