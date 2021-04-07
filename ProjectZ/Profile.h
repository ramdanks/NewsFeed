#pragma once
#include <wx/wx.h>

#define PROFILE_PICTURE_WIDTH 35
#define PROFILE_PICTURE_HEIGHT 35

class Profile : public wxPanel 
{
public:
	Profile(wxWindow* parent);

private:
	void BuildGUI();

	wxDECLARE_EVENT_TABLE();
};

