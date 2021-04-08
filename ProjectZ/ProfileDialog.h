#pragma once
#include <wx/wx.h>
#include "Profile.h"

class ProfileDialog : public wxDialog
{
public:
	ProfileDialog(const sProfile& info, wxWindow* parent);
};

