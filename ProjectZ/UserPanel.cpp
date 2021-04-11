#include "UserPanel.h"
#include "Image.h"
#include "Theme.h"
#include "Id.h"
#include "ProfileDialog.h"

#define BIO_CHAR_LIMIT 30

wxPanel* UserPanel::sPanel;
sProfile UserPanel::sUser;
wxStaticText* UserPanel::sName;
wxStaticText* UserPanel::sBio;

void UserPanel::SetDisplayname(const wxString& name)
{
	sName->SetLabel(name);
}

void UserPanel::SetBio(const wxString& bio)
{
	if (sUser.bio.length() <= BIO_CHAR_LIMIT)
		sBio->SetLabel(bio);
	else
	{
		wxString str = bio;
		str.Truncate(BIO_CHAR_LIMIT);
		for (int i = BIO_CHAR_LIMIT - 4; i < BIO_CHAR_LIMIT; i++)
			str[i] = '\.';
		str[BIO_CHAR_LIMIT - 1] = '\0';
		sBio->SetLabel(str);
	}
}

void UserPanel::Init(wxWindow* parent, sProfile&& profile)
{
	sPanel = new wxPanel(parent);
	sUser = std::move(profile);
	BuildGUI();
}

void UserPanel::Init(wxWindow* parent, const sProfile& profile)
{
	sPanel = new wxPanel(parent);
	sUser = profile;
	BuildGUI();
}

wxPanel* UserPanel::Get()
{
	return UserPanel::sPanel;
}

sProfile UserPanel::GetUser()
{
	return UserPanel::sUser;
}

void UserPanel::OnSettingBtn(wxCommandEvent& event)
{
	wxCommandEvent postE(EVT_UP_SETTING);
	wxPostEvent(sPanel->GetParent(), postE);
}

void UserPanel::OnPictureBtn(wxCommandEvent& event)
{
	wxCommandEvent currE(EVT_UP_IMG);
	currE.SetClientData(&sUser);
	wxPostEvent(sPanel->GetParent(), currE);
}

void UserPanel::BuildGUI()
{
	Theme::SetWindow(sPanel, CLR_PROFILE_BACK, CLR_PROFILE_FORE);
	sPanel->Bind(wxEVT_BUTTON, &UserPanel::OnPictureBtn, ID_USER_PICTURE_BTN);
	sPanel->Bind(wxEVT_BUTTON, &UserPanel::OnSettingBtn, ID_USER_SETTING_BTN);
	
	auto* sizer0 = new wxBoxSizer(wxVERTICAL);
	auto* sizer1 = new wxBoxSizer(wxVERTICAL);
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	// load profile picture
	auto pict = sUser.picture;
	Image::SetBitmapScale(pict, USER_PICTURE_WIDTH, USER_PICTURE_HEIGHT);
	wxBitmapButton* pp = new wxBitmapButton(sPanel, ID_USER_PICTURE_BTN, pict);

	sName = new wxStaticText(sPanel, -1, sUser.displayname);
	auto* setting = new wxButton(sPanel, ID_USER_SETTING_BTN, "", wxPoint(0,0), wxSize(30,30));
	
	sBio = new wxStaticText(sPanel, -1, "");
	SetBio(sUser.bio);

	sizer1->Add(sName);
	sizer1->AddSpacer(2);
	sizer1->Add(sBio);

	sName->SetFont(FONT_PROFILE);

	sizer->Add(pp, 0, wxLEFT, 10);
	sizer->Add(sizer1, 0, wxLEFT, 5);
	sizer->AddStretchSpacer();
	sizer->Add(setting, 0, wxCENTER | wxLEFT | wxRIGHT, 10);

	sizer0->AddSpacer(10);
	sizer0->Add(sizer, 0, wxEXPAND);
	sizer0->AddSpacer(10);

	sPanel->SetSizer(sizer0);
	sizer0->SetSizeHints(sPanel);
}