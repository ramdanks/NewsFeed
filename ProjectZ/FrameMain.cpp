#include "FrameMain.h"
#include "Instrumentator.h"

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
	PROFILE_FUNC();
	this->SetBackgroundColour(wxColour(50, 50, 50));
	this->SetForegroundColour(wxColour(240, 240, 240));
}