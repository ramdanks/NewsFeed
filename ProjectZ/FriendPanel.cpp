#include "FriendPanel.h"
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

void FriendPanel::BuildGUI()
{
	Theme::SetWindow(this, CLR_FRIEND_IDLE_BACK, CLR_FRIEND_IDLE_FORE);
}

void FriendPanel::OnMouseMove(wxMouseEvent& event)
{
}

void FriendPanel::OnMouseLPress(wxMouseEvent& event)
{
}

void FriendPanel::OnMouseLRelease(wxMouseEvent& event)
{
}

void FriendPanel::OnMouseRClick(wxMouseEvent& event)
{
}

void FriendPanel::OnMouseEnter(wxMouseEvent& event)
{
	mFocus = true;
	Theme::SetWindow(this, CLR_FRIEND_FOCUS_BACK, CLR_FRIEND_FOCUS_FORE);
	this->Refresh();
}

void FriendPanel::OnMouseLeave(wxMouseEvent& event)
{
	mFocus = false;
	Theme::SetWindow(this, CLR_FRIEND_IDLE_BACK, CLR_FRIEND_IDLE_FORE);
	this->Refresh();
}
