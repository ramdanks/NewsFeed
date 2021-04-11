#include "FeedEntry.h"
#include "Theme.h"
#include "Image.h"
#include "Id.h"
#include "FlagSetting.h"

BEGIN_EVENT_TABLE(FeedEntry, wxPanel)
EVT_BUTTON(ID_FLAG_BTN, FeedEntry::OnFlagBtn)
EVT_BUTTON(ID_POST_BTN, FeedEntry::OnPostBtn)
END_EVENT_TABLE()

FeedEntry::FeedEntry(wxWindow* parent)
	: wxPanel(parent)
{
	BuildGUI();
}

void FeedEntry::OnFlagBtn(wxCommandEvent& event)
{
	std::vector<wxString> flags;
	flags.reserve(mFlags.size());
	for (auto& i : mFlags)
		flags.emplace_back(i.second);
	FlagSetting f(this, flags);
	f.ShowModal();

	auto newlist = f.GetFlagList();
	mCombo->Set(newlist);
}

void FeedEntry::OnPostBtn(wxCommandEvent& event)
{
	try
	{
		if (mCombo->GetSelection() == wxNOT_FOUND)
			throw "Please select a flag!\nIf you don't have any, create one by cliking flag logo";
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

	mFlags[1] = "Libur";
	mFlags[2] = "Beasiswa";
	std::vector<wxString> flags;
	flags.reserve(mFlags.size());
	for (auto& i : mFlags)
		flags.emplace_back(i.second);

	auto* postBtn = new wxButton(this, ID_POST_BTN, "Post");
	
	auto img = Image::GetImage(FLAG_PNG);
	img.Rescale(15, 15);

	auto* flagImg = new wxBitmapButton(this, ID_FLAG_BTN, wxBitmap(img));
	mCombo = new wxChoice(this, -1, wxPoint(0,0), wxSize(120,0));
	mCombo->Set(flags);
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