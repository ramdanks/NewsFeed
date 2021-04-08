#include "ProfileDialog.h"

ProfileDialog::ProfileDialog(const sProfile& info, wxWindow* parent)
	: wxDialog(parent, -1, "Profile")
{
	auto* sizer = new wxBoxSizer(wxVERTICAL);

	auto* name = new wxStaticText(this, -1, info.name);
	auto* bio = new wxStaticText(this, -1, info.bio);
	auto* pict = new wxStaticBitmap(this, -1, info.picture);

	sizer->Add(pict);
	sizer->Add(name);
	sizer->Add(bio);

	this->SetSizer(sizer);
	sizer->SetSizeHints(this);
}