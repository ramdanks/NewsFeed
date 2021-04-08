#pragma once
#include <wx/wx.h>

#define USER_PICTURE_WIDTH  35
#define USER_PICTURE_HEIGHT 35

class UserPanel : public wxPanel
{
public:
	UserPanel(wxWindow* parent);

private:
	void BuildGUI();

	wxDECLARE_EVENT_TABLE();
};