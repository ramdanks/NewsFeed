#include "Profile.h"
#include "Image.h"

wxBEGIN_EVENT_TABLE(Profile, wxPanel)
wxEND_EVENT_TABLE()

Profile::Profile(wxWindow* parent)
	: wxPanel(parent)
{
	BuildGUI();
}

void Profile::BuildGUI()
{
	wxBitmapButton* pp;
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
	auto* setting = new wxButton(this, -1);

	sizer->Add(pp, 0, wxLEFT | wxRIGHT, 10);
	sizer->Add(name, 0, wxLEFT | wxRIGHT, 10);
	sizer->AddStretchSpacer(1);
	sizer->Add(setting, 0, wxLEFT | wxRIGHT, 10);

	this->SetSizer(sizer);
	sizer->SetSizeHints(this);
}