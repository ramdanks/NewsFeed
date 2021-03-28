#pragma once
#include <wx/wx.h>

class FrameMain : public wxFrame
{
public:
	FrameMain();
	FrameMain(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	void BuildGUI();
};