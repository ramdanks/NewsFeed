#pragma once
#include <wx/wx.h>

class FriendWindow : public wxScrolledWindow
{
public:
	FriendWindow(wxWindow* parent);
	
private:
	void BuildGUI();
};

