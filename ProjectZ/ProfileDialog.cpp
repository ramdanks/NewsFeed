#include "ProfileDialog.h"
#include "Theme.h"

ProfileDialog::ProfileDialog(const sProfile& info, wxWindow* parent)
	: wxDialog(parent, -1, "Profile", wxDefaultPosition, wxSize(200, 200))
{
	Theme::SetWindow(this, CLR_PROFILE_BACK, CLR_PROFILE_FORE);

	auto* sizer = new wxBoxSizer(wxVERTICAL);

	auto img = info.picture.ConvertToImage();
	img.Rescale(80, 80);

	auto* name = new wxStaticText(this, -1, info.displayname);
	auto* bio = new wxStaticText(this, -1, info.bio);
	auto* pict = new wxStaticBitmap(this, -1, wxBitmap(img));

	name->SetFont(FONT_PROFILE);

	sizer->Add(pict, 1, wxEXPAND);
	sizer->Add(name, 0, wxCENTER | wxLEFT | wxRIGHT, 15);
	sizer->AddSpacer(10);
	sizer->Add(bio, 0, wxCENTER | wxLEFT | wxRIGHT, 15);
	sizer->AddSpacer(10);

	this->SetSizer(sizer);
}