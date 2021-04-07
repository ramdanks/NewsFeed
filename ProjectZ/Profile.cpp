#include "Profile.h"
#include "Image.h"
#include "Theme.h"

wxBEGIN_EVENT_TABLE(Profile, wxPanel)
wxEND_EVENT_TABLE()

Profile::Profile(wxWindow* parent)
	: wxPanel(parent)
{
	BuildGUI();
}

void Profile::BuildGUI()
{
	Theme::SetWindow(this, CLR_PROFILE_BACK, CLR_PROFILE_FORE);

	wxBitmapButton* pp;
	auto* sizer0 = new wxBoxSizer(wxVERTICAL);
	auto* sizer1 = new wxBoxSizer(wxVERTICAL);
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	// load profile picture
	auto bmp = Image::GetImage(PROFILE_IMG);
	if (bmp.GetWidth() != PROFILE_PICTURE_WIDTH ||
		bmp.GetHeight() != PROFILE_PICTURE_HEIGHT)
	{
		auto img = bmp.ConvertToImage();
		img.Rescale(35, 35);
		pp = new wxBitmapButton(this, -1, img);
	}
	else
	{
		pp = new wxBitmapButton(this, -1, bmp);
	}

	auto* name = new wxStaticText(this, -1, "myname");
	auto* email = new wxStaticText(this, -1, "ramadhan.kalih@ui.ac.id");
	auto* setting = new wxButton(this, -1);

	sizer1->Add(name);
	sizer1->AddSpacer(2);
	sizer1->Add(email);

	name->SetFont(FONT_PROFILE);

	sizer->Add(pp, 0, wxLEFT, 10);
	sizer->Add(sizer1, 0, wxLEFT, 5);
	sizer->AddStretchSpacer();
	sizer->Add(setting, 0, wxLEFT | wxRIGHT, 10);

	sizer0->AddSpacer(10);
	sizer0->Add(sizer, 0, wxEXPAND);
	sizer0->AddSpacer(10);

	this->SetSizer(sizer0);
	sizer0->SetSizeHints(this);
}