#pragma once
#include <wx/wx.h>
#include "FrameMain.h"

class App : public wxApp
{
public:
	App();
	~App();

public:
	bool OnInit() override;
	int OnExit() override;

private:
	FrameMain* mpFrameMain;
};