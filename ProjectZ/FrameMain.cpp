#include "FrameMain.h"
#include "Instrumentator.h"
#include "MD5.h"
#include "Id.h"
#include "Dashboard.h"
#include <pqxx/pqxx>
#include <wx/regex.h>
#include <wx/busyinfo.h>

wxBEGIN_EVENT_TABLE(FrameMain, wxFrame)
EVT_BUTTON(ID_LOGIN_BTN, FrameMain::OnLoginBtn)
EVT_HYPERLINK(ID_FORGOT_LINK, FrameMain::OnForgotLink)
EVT_HYPERLINK(ID_SIGNUP_LINK, FrameMain::OnSignupLink)
EVT_CLOSE(FrameMain::OnClose)
wxEND_EVENT_TABLE()

FrameMain::FrameMain(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	PROFILE_SCOPE("Create Landing Page");
	this->BuildGUI();
}

void FrameMain::Quit()
{
	this->Hide();
	this->Destroy();
}

void FrameMain::BuildGUI()
{
#define GENERAL_LEN 200

	PROFILE_FUNC();
	this->SetBackgroundColour(wxColour(50, 50, 50));
	this->SetForegroundColour(wxColour(240, 240, 240));

	auto* sizer = new wxBoxSizer(wxVERTICAL);

	wxBitmap bm("IMG_LOGO", wxBITMAP_TYPE_PNG_RESOURCE);
	auto* logo = new wxStaticBitmap(this, wxID_ANY, bm);
	auto* brand = new wxStaticText(this, wxID_ANY, "Elearning");
	auto myFont = brand->GetFont();
	myFont.SetPointSize(20);
	brand->SetFont(myFont);

	auto* sizer0 = new wxBoxSizer(wxHORIZONTAL);
	sizer0->Add(logo, 0, wxRIGHT, 8);
	sizer0->Add(brand, 0, wxALIGN_CENTER_VERTICAL);

	mUserCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
								wxSize(GENERAL_LEN, 22), wxBORDER_NONE);
	mPassCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
								wxSize(GENERAL_LEN, 22), wxBORDER_NONE | wxTE_PASSWORD);

	wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Calibri");

	mUserCtrl->SetForegroundColour(wxColour(240, 240, 240));
	mUserCtrl->SetBackgroundColour(wxColour(30, 30, 30));

	mPassCtrl->SetForegroundColour(wxColour(240, 240, 240));
	mPassCtrl->SetBackgroundColour(wxColour(30, 30, 30));

	mUserCtrl->SetFont(font);
	mPassCtrl->SetFont(font);

	mUserCtrl->SetHint("Username");
	mPassCtrl->SetHint("Password");

	mWarn = new wxStaticText(this, wxID_ANY, "");
	mWarn->SetForegroundColour(wxColour(250, 50, 50));

	auto* userText = new wxStaticText(this, wxID_ANY, "Username");
	auto* passText = new wxStaticText(this, wxID_ANY, "Password");
	auto* rememberBox = new wxCheckBox(this, wxID_ANY, "Remember Me");

	myFont.SetPointSize(10);
	myFont.MakeBold();
	userText->SetFont(myFont);
	passText->SetFont(myFont);

	auto* loginBtn = new wxButton(this, ID_LOGIN_BTN, "Log In", wxDefaultPosition, wxSize(GENERAL_LEN, 30));

	auto* nohaveText = new wxStaticText(this, wxID_ANY, "Don't have an account?");
	auto* signup = new wxGenericHyperlinkCtrl(this, ID_SIGNUP_LINK, "Sign Up", "");
	auto* forgot = new wxGenericHyperlinkCtrl(this, ID_FORGOT_LINK, "Forgot Password?", "");

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

	sizer->AddSpacer(25);
	sizer->Add(sizer0, 0, wxCENTER | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(15);
	sizer->Add(mWarn, 0, wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(8);
	sizer->Add(userText, 0, wxLEFT | wxRIGHT, 30);
	sizer->Add(mUserCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
	sizer->AddSpacer(10);
	sizer->Add(passText, 0, wxLEFT | wxRIGHT, 30);
	sizer->Add(mPassCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
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

void FrameMain::OnClose(wxCloseEvent& event)
{
	Quit();
}

void FrameMain::OnLoginBtn(wxCommandEvent& event)
{
	PROFILE_BEGIN("Login", "Profiling/Login.json");

	static const char opt[] = "host=localhost port=5432 dbname=projectz_db user=postgres";
	static char buff[1024];
	std::string hashpass;
	std::string username;
	wxBusyCursor busy;

	try
	{
		{
			PROFILE_SCOPE("Username Validation");
			wxString user = mUserCtrl->GetLineText(0);
			static wxRegEx keyword("^[A-Za-z0-9]*$");
			if (user.empty())
				throw wxString("Please insert your username!");
			if (!keyword.Matches(user))
				throw wxString("Incorrect username!");
			username = user.ToStdString();
		}
		{
			PROFILE_SCOPE("MD5 Hash");
			wxString pass = mPassCtrl->GetLineText(0);
			if (pass.empty())
				throw wxString("Please insert your password!");
			hashpass = md5(pass.ToStdString());
		}
		{
			PROFILE_SCOPE("Server Authenthication");
			pqxx::connection con(opt);
			pqxx::work work(con);

			_snprintf(buff, sizeof(buff), "SELECT EXISTS(SELECT 1 FROM Account WHERE username='%s' and password='%s')", username.c_str(), hashpass.c_str());
			pqxx::result res = work.exec(buff);
			bool valid = res[0][0].as<bool>();
			if (!valid)
				throw wxString("Wrong credential, try again!");
		}
	}
	catch (wxString& msg)
	{
		PROFILE_END();
		mWarn->SetLabel(msg);
		return;
	}

	PROFILE_END();
	
	mWarn->SetLabel("");
	this->Hide();
	auto* dashboard = new Dashboard(this);
	dashboard->Show();
}

void FrameMain::OnForgotLink(wxHyperlinkEvent& event)
{
}

void FrameMain::OnSignupLink(wxHyperlinkEvent& event)
{
}
