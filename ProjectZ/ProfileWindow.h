#pragma once
#include <wx/wx.h>

class ProfileWindow : public wxScrolledWindow
{
public:
	ProfileWindow(wxWindow* parent);
	
private:
	void BuildGUI();
};

