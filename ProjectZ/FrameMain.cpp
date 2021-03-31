#include "FrameMain.h"
#include "Instrumentator.h"
#include "MD5.h"
#include "Id.h"
#include "Dashboard.h"
#include "DBRequest.h"
#include <wx/regex.h>
#include <wx/busyinfo.h>

wxBEGIN_EVENT_TABLE(FrameMain, wxFrame)
EVT_BUTTON(ID_LOGIN_BTN, FrameMain::OnLoginBtn)
EVT_BUTTON(ID_SIGNUP_BTN, FrameMain::OnSignupBtn)
EVT_HYPERLINK(ID_FORGOT_LINK, FrameMain::OnForgotLink)
EVT_HYPERLINK(ID_SIGNUP_LINK, FrameMain::OnSignupLink)
EVT_HYPERLINK(ID_LOGIN_LINK, FrameMain::OnLoginLink)
EVT_AUINOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK_LANDING, FrameMain::OnPageChanged)
EVT_CLOSE(FrameMain::OnClose)
wxEND_EVENT_TABLE()

constexpr long frameStyle = wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxSYSTEM_MENU;

FrameMain::FrameMain(const wxString& title, const wxPoint& pos)
	: wxFrame(nullptr, wxID_ANY, title, pos, WND_LOGIN_SIZE, frameStyle),
	mMode(LandingMode::LOGIN)
{
	PROFILE_SCOPE("Create Landing Page");
	this->BuildGUI();
	if (!DBRequest::Init())
	{
		wxBusyInfo info("Warning: Cannot communicate with the database!");
		wxThread::This()->Sleep(2000);
	}
}

FrameMain::LandingMode FrameMain::GetMode() const
{
	return mMode;
}

void FrameMain::SetMode(LandingMode mode)
{
	mMode = mode;
	this->Freeze();
	this->BuildGUI();
	this->Thaw();
}

void FrameMain::Quit()
{
	this->Hide();
	this->Destroy();
}

#define GENERAL_LEN 200
void FrameMain::BuildGUI()
{
	PROFILE_FUNC();

	wxFont entryFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Roboto");

	const wxColour uiFore = wxColour(230, 230, 230);
	const wxColour uiBack = wxColour(40, 40, 40);
	const wxColour entryFore = wxColour(250, 250, 250);
	const wxColour entryBack = wxColour(25, 25, 25);

	wxPanel* lPanel = new wxPanel(this, wxID_ANY);
	wxPanel* rPanel = new wxPanel(this, wxID_ANY);

	auto SetTheme = [](wxWindow* wnd, const wxColour& back, const wxColour& fore)
	{
		wnd->SetBackgroundColour(back);
		wnd->SetForegroundColour(fore);
	};
	auto SetHyperlinkColour = [](wxGenericHyperlinkCtrl* link)
	{
		link->SetNormalColour(wxColour(255, 255, 255));
		link->SetHoverColour(wxColour(52, 180, 240));
		link->SetVisitedColour(wxColour(255, 255, 255));
	};
	auto CreateHeader = [](wxWindow* wnd) -> wxSizer*
	{
		// set logo and title
		wxBitmap bm("IMG_LOGO", wxBITMAP_TYPE_PNG_RESOURCE);
		auto* myLogo = new wxStaticBitmap(wnd, wxID_ANY, bm);
		auto* myName = new wxStaticText(wnd, wxID_ANY, "Elearning");
		auto myFont = myName->GetFont();
		myFont.SetPointSize(20);
		myName->SetFont(myFont);

		// add to sizer0
		auto* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(myLogo, 0, wxRIGHT, 8);
		sizer->Add(myName, 0, wxALIGN_CENTER_VERTICAL);
		return sizer;
	};

	// set background and foreground color
	SetTheme(lPanel, uiBack, uiFore);
	SetTheme(rPanel, uiBack, uiFore);
	// create warning text
	mReg.Warn = new wxStaticText(rPanel, wxID_ANY, "");
	mLog.Warn = new wxStaticText(lPanel, wxID_ANY, "");

	// Create Login Panel
	{
		auto* sizer0 = CreateHeader(lPanel);
		auto* sizer = new wxBoxSizer(wxVERTICAL);

		auto* uctrl = new wxTextCtrl(lPanel, wxID_ANY, "", wxPoint(0, 0), wxSize(GENERAL_LEN, 22), wxBORDER_NONE);
		auto* pctrl = new wxTextCtrl(lPanel, wxID_ANY, "", wxPoint(0, 0), wxSize(GENERAL_LEN, 22), wxBORDER_NONE | wxTE_PASSWORD);

		SetTheme(uctrl, entryBack, entryFore);
		SetTheme(pctrl, entryBack, entryFore);
		uctrl->SetFont(entryFont);
		pctrl->SetFont(entryFont);
		uctrl->SetHint("Username");
		pctrl->SetHint("Password");

		auto* utext = new wxStaticText(lPanel, wxID_ANY, "Username");
		auto* ptext = new wxStaticText(lPanel, wxID_ANY, "Password");
		auto* rbox = new wxCheckBox(lPanel, wxID_ANY, "Remember Me");

		auto* loginBtn = new wxButton(lPanel, ID_LOGIN_BTN, "Log In", wxDefaultPosition, wxSize(GENERAL_LEN, 30));

		auto* nohaveText = new wxStaticText(lPanel, wxID_ANY, "Don't have an account?");
		auto* signup = new wxGenericHyperlinkCtrl(lPanel, ID_SIGNUP_LINK, "Sign Up", "");
		auto* forgot = new wxGenericHyperlinkCtrl(lPanel, ID_FORGOT_LINK, "Forgot Password?", "");

		SetHyperlinkColour(signup);
		SetHyperlinkColour(forgot);

		auto* sizer1 = new wxBoxSizer(wxHORIZONTAL);
		sizer1->Add(rbox, 0, wxRIGHT, 30);
		sizer1->AddStretchSpacer();
		sizer1->Add(forgot);

		auto* sizer2 = new wxBoxSizer(wxHORIZONTAL);
		sizer2->Add(nohaveText, 0, wxRIGHT, 8);
		sizer2->Add(signup);

		sizer->AddSpacer(25);
		sizer->Add(sizer0, 0, wxCENTER | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(15);
		sizer->Add(mLog.Warn, 0, wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(8);
		sizer->Add(utext, 0, wxLEFT | wxRIGHT, 30);
		sizer->Add(uctrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(10);
		sizer->Add(ptext, 0, wxLEFT | wxRIGHT, 30);
		sizer->Add(pctrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(10);
		sizer->Add(sizer1, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(15);
		sizer->Add(loginBtn, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(15);
		sizer->Add(sizer2, 0, wxCENTER | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(25);

		lPanel->SetSizer(sizer);
		sizer->SetSizeHints(lPanel);

		mLog.UserCtrl = uctrl;
		mLog.PassCtrl = pctrl;
	}
	// Create Signup Panel
	{
		auto* sizer0 = CreateHeader(rPanel);
		auto* sizer = new wxBoxSizer(wxVERTICAL);

		auto* uctrl = new wxTextCtrl(rPanel, wxID_ANY, "", wxPoint(0, 0), wxSize(GENERAL_LEN, 22), wxBORDER_NONE);
		auto* ectrl = new wxTextCtrl(rPanel, wxID_ANY, "", wxPoint(0, 0), wxSize(GENERAL_LEN, 22), wxBORDER_NONE);
		auto* pctrl = new wxTextCtrl(rPanel, wxID_ANY, "", wxPoint(0, 0), wxSize(GENERAL_LEN, 22), wxBORDER_NONE | wxTE_PASSWORD);
		auto* cctrl = new wxTextCtrl(rPanel, wxID_ANY, "", wxPoint(0, 0), wxSize(GENERAL_LEN, 22), wxBORDER_NONE | wxTE_PASSWORD);

		SetTheme(uctrl, entryBack, entryFore);
		SetTheme(ectrl, entryBack, entryFore);
		SetTheme(pctrl, entryBack, entryFore);
		SetTheme(cctrl, entryBack, entryFore);
		uctrl->SetFont(entryFont);
		ectrl->SetFont(entryFont);
		pctrl->SetFont(entryFont);
		cctrl->SetFont(entryFont);
		uctrl->SetHint("Username");
		ectrl->SetHint("Email");
		pctrl->SetHint("Password");
		cctrl->SetHint("Password");

		auto* utext = new wxStaticText(rPanel, wxID_ANY, "Username");
		auto* etext = new wxStaticText(rPanel, wxID_ANY, "Email");
		auto* ptext = new wxStaticText(rPanel, wxID_ANY, "Password");
		auto* ctext = new wxStaticText(rPanel, wxID_ANY, "Confirm Password");
		mReg.Terms  = new wxCheckBox(rPanel, wxID_ANY, "I accept the terms and conditions");

		auto* registerBtn = new wxButton(rPanel, ID_SIGNUP_BTN, "Create my Account", wxDefaultPosition, wxSize(GENERAL_LEN, 30));

		auto* nohaveText = new wxStaticText(rPanel, wxID_ANY, "Already have an account?");
		auto* signup = new wxGenericHyperlinkCtrl(rPanel, ID_LOGIN_LINK, "Log In", "");

		SetHyperlinkColour(signup);

		auto* sizer2 = new wxBoxSizer(wxHORIZONTAL);
		sizer2->Add(nohaveText, 0, wxRIGHT, 8);
		sizer2->Add(signup);

		sizer->AddSpacer(25);
		sizer->Add(sizer0, 0, wxCENTER | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(15);
		sizer->Add(mReg.Warn, 0, wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(8);
		sizer->Add(utext, 0, wxLEFT | wxRIGHT, 30);
		sizer->Add(uctrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(10);
		sizer->Add(etext, 0, wxLEFT | wxRIGHT, 30);
		sizer->Add(ectrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(10);
		sizer->Add(ptext, 0, wxLEFT | wxRIGHT, 30);
		sizer->Add(pctrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(10);
		sizer->Add(ctext, 0, wxLEFT | wxRIGHT, 30);
		sizer->Add(cctrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(10);
		sizer->Add(mReg.Terms, 0, wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(15);
		sizer->Add(registerBtn, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(15);
		sizer->Add(sizer2, 0, wxCENTER | wxLEFT | wxRIGHT, 30);
		sizer->AddSpacer(25);

		rPanel->SetSizer(sizer);
		sizer->SetSizeHints(rPanel);

		mReg.UserCtrl = uctrl;
		mReg.EmailCtrl = ectrl;
		mReg.PassCtrl = pctrl;
		mReg.PassConfirmCtrl = cctrl;
	}
	
	mNotebook = new wxAuiNotebook(this, ID_NOTEBOOK_LANDING);
	mNotebook->SetWindowStyle(wxAUI_NB_TOP | wxAUI_NB_TAB_FIXED_WIDTH);
	mNotebook->AddPage(lPanel, "Log In");
	mNotebook->AddPage(rPanel, "Sign Up");
	mNotebook->SetBackgroundColour(wxColour(0, 0, 0));
}

void FrameMain::Warn(const wxString& msg, bool ok)
{
	static const wxColour GREEN = wxColour(70, 255, 70);
	static const wxColour RED   = wxColour(255, 70, 70);
	if (ok)
	{
		mReg.Warn->SetForegroundColour(GREEN);
		mLog.Warn->SetForegroundColour(GREEN);
	}
	else
	{
		mReg.Warn->SetForegroundColour(RED);
		mLog.Warn->SetForegroundColour(RED);
	}
	mLog.Warn->SetLabel(msg);
	mReg.Warn->SetLabel(msg);
}

void FrameMain::OnClose(wxCloseEvent& event)
{
	Quit();
}

void FrameMain::OnLoginBtn(wxCommandEvent& event)
{
	PROFILE_BEGIN("Login", "Profiling/Login.json");

	std::string hashpass;
	std::string username;
	wxBusyCursor busy;

	try
	{
		{
			PROFILE_SCOPE("Username Validation");
			wxString user = mLog.UserCtrl->GetLineText(0);
			static wxRegEx keyword("^[A-Za-z0-9]*$");
			if (user.empty())
				throw wxString("Please insert your username!");
			if (!keyword.Matches(user))
				throw wxString("Incorrect username!");
			username = user.ToStdString();
		}
		{
			PROFILE_SCOPE("Password Validation");
			wxString pass = mLog.PassCtrl->GetLineText(0);
			if (pass.empty())
				throw wxString("Please insert your password!");
			hashpass = md5(pass.ToStdString());
		}
		{
			PROFILE_SCOPE("Server Authenthication");
			if (!DBRequest::Login(username, hashpass))
				throw wxString("Wrong credential, try again!");
		}
	}
	catch (wxString& msg)
	{
		PROFILE_END();
		Warn(msg);
		return;
	}
	catch (...)
	{
		PROFILE_END();
		Warn("Database connection error!");
		return;
	}

	PROFILE_END();
	
	mLog.Warn->SetLabel("");
	this->Hide();
	auto* dashboard = new Dashboard(this);
	dashboard->Show();
}

void FrameMain::OnSignupBtn(wxCommandEvent& event)
{
	PROFILE_BEGIN("Login", "Profiling/Register.json");

	std::string hashpass;
	std::string username;
	std::string email;
	wxBusyCursor busy;

	try
	{
		{
			PROFILE_SCOPE("Username Validation");
			static const wxRegEx keyword("^[a-zA-Z0-9]*$");
			wxString user = mReg.UserCtrl->GetLineText(0);
			if (user.empty())
				throw wxString("Please insert your username!");
			if (!keyword.Matches(user))
				throw wxString("Incorrect username!");
			username = user.ToStdString();
		}
		{
			PROFILE_SCOPE("Email Validation");
			static const wxRegEx keyword("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$");
			wxString em = mReg.EmailCtrl->GetLineText(0);
			if (em.empty())
				throw wxString("Please insert your email!");
			if (!keyword.Matches(em))
				throw wxString("Please insert a valid email!");
			email = em.ToStdString();
		}
		{
			PROFILE_SCOPE("Password Validation");
			wxString pass1 = mReg.PassCtrl->GetLineText(0);
			wxString pass2 = mReg.PassConfirmCtrl->GetLineText(0);
			if (pass1.empty())
				throw wxString("Please insert your password!");
			if (pass2.empty())
				throw wxString("Please confirm your password!");
			if (pass1 != pass2)
				throw wxString("Password do not match!");
			hashpass = md5(pass1.ToStdString());
		}
		{
			PROFILE_SCOPE("Terms and Conditions Validation");
			if (!mReg.Terms->GetValue())
				throw wxString("Please accept the terms and conditions!");
		}
		{
			PROFILE_SCOPE("Server Signup");
			if (DBRequest::UserExist(username))
				throw wxString("Oops, username already taken!");
			if (!DBRequest::Signup(username, hashpass, email))
				throw wxString("Database couldn't register!");
		}
	}
	catch (wxString& msg)
	{
		PROFILE_END();
		Warn(msg);
		return;
	}
	catch (...)
	{
		PROFILE_END();
		Warn("Database connection error!");
		return;
	}
	PROFILE_END();
	Warn("Signup Complete!", true);
}

void FrameMain::OnForgotLink(wxHyperlinkEvent& event)
{
}

void FrameMain::OnSignupLink(wxHyperlinkEvent& event)
{
	this->Freeze();
	mNotebook->SetSelection(1);
	wxAuiNotebookEvent evt;
	OnPageChanged(evt);
	this->Thaw();
}

void FrameMain::OnLoginLink(wxHyperlinkEvent& event)
{
	this->Freeze();
	mNotebook->SetSelection(0);
	wxAuiNotebookEvent evt;
	OnPageChanged(evt);
	this->Thaw();
}

void FrameMain::OnPageChanged(wxAuiNotebookEvent& event)
{
	auto sel = mNotebook->GetSelection();
	if (sel != wxNOT_FOUND)
	{
		Warn("");
		if (sel == 0)
		{
			mMode = LOGIN;
			this->SetSize(WND_LOGIN_SIZE);
		}
		else
		{
			mMode = SIGNUP;
			this->SetSize(WND_SIGNUP_SIZE);
		}
	}
}
