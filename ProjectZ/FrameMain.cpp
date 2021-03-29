#include "FrameMain.h"
#include "Instrumentator.h"
#include <wx/hyperlink.h>

FrameMain::FrameMain()
	: wxFrame(nullptr, wxID_ANY, "Log In", wxDefaultPosition, wxSize(400, 300))
{
	PROFILE_SCOPE("Create Main Frame");
	this->BuildGUI();
}

FrameMain::FrameMain(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	PROFILE_SCOPE("Create Main Frame");
	this->BuildGUI();
}

void FrameMain::BuildGUI()
{
	PROFILE_FUNC();
	this->SetBackgroundColour(wxColour(50, 50, 50));
	this->SetForegroundColour(wxColour(240, 240, 240));

	auto* sizer = new wxBoxSizer(wxVERTICAL);

#define GENERAL_LEN 200
	auto* userCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
									wxSize(GENERAL_LEN, 22), wxBORDER_NONE);
	auto* passCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
									wxSize(GENERAL_LEN, 22), wxBORDER_NONE | wxTE_PASSWORD);

	wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Calibri");

	userCtrl->SetForegroundColour(wxColour(255, 255, 255));
	userCtrl->SetBackgroundColour(wxColour(30, 30, 30));

	passCtrl->SetForegroundColour(wxColour(255, 255, 255));
	passCtrl->SetBackgroundColour(wxColour(30, 30, 30));

	userCtrl->SetFont(font);
	passCtrl->SetFont(font);

	userCtrl->SetHint("Username");
	passCtrl->SetHint("Password");

	auto* userText = new wxStaticText(this, wxID_ANY, "Username:");
	auto* passText = new wxStaticText(this, wxID_ANY, "Password:");
	auto* rememberBox = new wxCheckBox(this, wxID_ANY, "Remember Me");

	auto* loginBtn = new wxButton(this, wxID_ANY, "Log In", wxDefaultPosition, wxSize(GENERAL_LEN, 30));

	auto* nohaveText = new wxStaticText(this, wxID_ANY, "Don't have an account?");
	auto* signup = new wxGenericHyperlinkCtrl(this, wxID_ANY, "Sign Up", "");
	auto* forgot = new wxGenericHyperlinkCtrl(this, wxID_ANY, "Forgot Password?", "");

	auto SetHyperlinkColour = [](wxGenericHyperlinkCtrl* link)
	{
		link->SetNormalColour(wxColour(255, 255, 255));
		link->SetHoverColour(wxColour(52, 180, 240));
		link->SetVisitedColour(wxColour(255, 255, 255));
	};

	SetHyperlinkColour(signup);
	SetHyperlinkColour(forgot);

	auto* sizer1 = new wxBoxSizer(wxHORIZONTAL);
	sizer1->Add(rememberBox, 0, wxRIGHT, 25);
	sizer1->AddStretchSpacer();
	sizer1->Add(forgot);

	auto* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	sizer2->Add(nohaveText, 0, wxRIGHT, 8);
	sizer2->Add(signup);

	wxBitmap bm("IMG_LOGO", wxBITMAP_TYPE_PNG_RESOURCE);
	auto* logo = new wxStaticBitmap(this, wxID_ANY, bm);
	auto* brand = new wxStaticText(this, wxID_ANY, "Elearning");
	auto myFont = brand->GetFont();
	myFont.SetPointSize(20);
	brand->SetFont(myFont);

	auto* sizer0 = new wxBoxSizer(wxHORIZONTAL);
	sizer0->Add(logo, 0, wxRIGHT, 8);
	sizer0->Add(brand, 0, wxALIGN_CENTER_VERTICAL);

	sizer->AddSpacer(25);
	sizer->Add(sizer0, 0, wxCENTER | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(25);
	sizer->Add(userText, 0, wxLEFT | wxRIGHT, 30);
	sizer->Add(userCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(10);
	sizer->Add(passText, 0, wxLEFT | wxRIGHT, 30);
	sizer->Add(passCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(10);
	sizer->Add(sizer1, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(15);
	sizer->Add(loginBtn, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(15);
	sizer->Add(sizer2, 0, wxCENTER | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(25);

	this->SetSizer(sizer);
	sizer->SetSizeHints(this);
}