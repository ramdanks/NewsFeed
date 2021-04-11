#include "FeedEntry.h"
#include "Theme.h"
#include "Image.h"
#include "Id.h"
#include "FlagSetting.h"
#include "DBRequest.h"
#include "UserPanel.h"

BEGIN_EVENT_TABLE(FeedEntry, wxPanel)
EVT_BUTTON(ID_FLAG_BTN, FeedEntry::OnFlagBtn)
EVT_BUTTON(ID_POST_BTN, FeedEntry::OnPostBtn)
END_EVENT_TABLE()

FeedEntry::FeedEntry(wxWindow* parent)
	: wxPanel(parent)
{
	BuildGUI();
}

void FeedEntry::SetFlag(const wxArrayString& flags)
{
	auto sel = mCombo->GetSelection();
	if (sel == wxNOT_FOUND) sel = 0;
	mCombo->Set(flags);
	mFlags = flags;
	mCombo->SetSelection(sel);
}

void FeedEntry::AddFlag(const wxString& flag)
{
	auto sel = mCombo->GetSelection();
	if (sel == wxNOT_FOUND) sel = 0;
	mCombo->Insert(flag, mCombo->GetCount());
	mFlags.Add(flag);
	mCombo->SetSelection(sel);
}

void FeedEntry::OnFlagBtn(wxCommandEvent& event)
{
	FlagSetting f(this, mFlags);
	f.ShowModal();

	auto newlist = f.GetFlagList();
	SetFlag(newlist);
}

void FeedEntry::OnPostBtn(wxCommandEvent& event)
{
	try
	{
		if (mCombo->GetSelection() == wxNOT_FOUND)
			throw "Please select a flag!\nIf you don't have any, create one by cliking flag logo";

		if (mSTC->IsEmpty())
			throw "Please enter a message to post!";

		auto text = mSTC->GetText();
		auto actor = UserPanel::GetUser().username.ToStdString();
		auto fid = DBRequest::GetFid(mCombo->GetStringSelection().ToStdString(), actor);

		auto pair = DBRequest::PostFeed(actor, text.ToStdString(), fid);

		if (pair.second.empty())
			throw "Oops, cannot commit to the database!";

		sFeed* f = new sFeed{pair.first, mCombo->GetStringSelection(), pair.second, text};
		
		wxCommandEvent event(EVT_FE_POST);
		event.SetClientData(f);
		wxPostEvent(GetParent(), event);
	}
	catch (const char* msg)
	{
		wxMessageBox(msg, "Invalid Post", wxICON_WARNING);
	}
}

void FeedEntry::BuildGUI()
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	auto* cmdSizer = new wxBoxSizer(wxVERTICAL);
	auto* flagSizer = new wxBoxSizer(wxHORIZONTAL);

	auto* postBtn = new wxButton(this, ID_POST_BTN, "Post");
	
	auto img = Image::GetImage(FLAG_PNG);
	img.Rescale(15, 15);

	auto* flagImg = new wxBitmapButton(this, ID_FLAG_BTN, wxBitmap(img));
	mCombo = new wxChoice(this, -1, wxPoint(0,0), wxSize(120,0));
	mCombo->SetSelection(0);

	flagSizer->Add(flagImg);
	flagSizer->Add(mCombo, 0, wxEXPAND);

	cmdSizer->Add(flagSizer, 0, wxEXPAND);
	cmdSizer->Add(postBtn, 1, wxEXPAND);

	mSTC = new wxStyledTextCtrl(this);
	mSTC->SetWrapMode(wxSTC_WRAP_WORD);
	sizer->Add(mSTC, 1, wxEXPAND);
	sizer->Add(cmdSizer, 0, wxEXPAND);
	this->SetSizer(sizer);
}