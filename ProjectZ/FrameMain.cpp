#include "FrameMain.h"

FrameMain::FrameMain()
	: wxFrame(nullptr, wxID_ANY, "Main", wxDefaultPosition, wxSize(400, 300))
{
	this->BuildGUI();
}

FrameMain::FrameMain(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	this->BuildGUI();
}

void FrameMain::BuildGUI()
{
	CreateStatusBar();
}