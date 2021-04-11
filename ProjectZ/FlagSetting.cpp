#include "FlagSetting.h"
#include "Id.h"
#include "wx/regex.h"
#include "Theme.h"

BEGIN_EVENT_TABLE(FlagSetting, wxDialog)
EVT_LISTBOX(ID_FLAG_LISTBOX, FlagSetting::OnListBox)
EVT_BUTTON(ID_FLAG_ADD, FlagSetting::OnAddFlags)
EVT_BUTTON(ID_FLAG_REMOVE, FlagSetting::OnRemoveFlags)
END_EVENT_TABLE()

FlagSetting::FlagSetting(wxWindow* parent, const std::vector<wxString>& flags)
	: wxDialog(parent, -1, "Flag Setting")
{
	BuildGUI(flags);
}

wxArrayString FlagSetting::GetFlagList()
{
	return mListbox->GetStrings();
}

void FlagSetting::OnAddFlags(wxCommandEvent& event)
{
	static wxRegEx keyword("^[a-zA-Z0-9]*$");
	wxString flag = mAddEntry->GetValue();
	try
	{
		if (flag.length() > 20)
			throw "Please use no more than 20 characters!";

		if (!keyword.Matches(flag))
			throw "Flags only use alphabet and digit character!";
		
		mListbox->AppendString(flag);
		mAddEntry->SetValue("");
	}
	catch (const char* msg)
	{
		wxMessageBox(msg, "Invalid Flag", wxICON_ERROR);
	}
}

void FlagSetting::OnRemoveFlags(wxCommandEvent& event)
{
	auto index = mListbox->FindString(mRemoveEntry->GetValue(), true);
	if (index != wxNOT_FOUND)
	{
		mListbox->Delete(index);
		mRemoveEntry->SetValue("");
	}
}

void FlagSetting::OnListBox(wxCommandEvent& event)
{
	auto* lb = (wxListBox*) event.GetEventObject();
	mRemoveEntry->SetLabel(lb->GetStringSelection());
}

void FlagSetting::BuildGUI(const std::vector<wxString>& flags)
{
	Theme::SetWindow(this, CLR_LANDING_BACK, CLR_LANDING_FORE);

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto aSizer = new wxBoxSizer(wxHORIZONTAL);
	auto rSizer = new wxBoxSizer(wxHORIZONTAL);

	auto* listtext = new wxStaticText(this, -1, "Flag List:");
	mListbox = new wxListBox(this, ID_FLAG_LISTBOX, wxDefaultPosition, wxSize(250,100));
	mListbox->Set(flags);

	Theme::SetWindow(mListbox, CLR_ENTRY_BACK, CLR_ENTRY_FORE);

	auto* ok = new wxButton(this, wxID_OK, "OK");
	auto* add = new wxButton(this, ID_FLAG_ADD, "Add Flags");
	auto* remove = new wxButton(this, ID_FLAG_REMOVE, "Remove Flags");

	mAddEntry = new wxTextCtrl(this, -1);
	mRemoveEntry = new wxTextCtrl(this, -1);

	Theme::SetWindow(mAddEntry, CLR_ENTRY_BACK, CLR_ENTRY_FORE);
	Theme::SetWindow(mRemoveEntry, CLR_ENTRY_BACK, CLR_ENTRY_FORE);

	mAddEntry->SetHint("Insert a new flag name");
	mRemoveEntry->SetHint("Choose from the list");

	aSizer->Add(add);
	aSizer->Add(mAddEntry, 1, wxEXPAND);
	
	rSizer->Add(remove);
	rSizer->Add(mRemoveEntry, 1 , wxEXPAND);

	sizer->AddSpacer(10);
	sizer->Add(aSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer->AddSpacer(10);
	sizer->Add(rSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer->AddSpacer(10);
	sizer->Add(listtext, 0, wxLEFT | wxRIGHT, 10);
	sizer->AddSpacer(5);
	sizer->Add(mListbox, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer->AddSpacer(10);
	sizer->Add(ok, 0, wxCENTER);
	sizer->AddSpacer(10);

	this->SetSizer(sizer);
	sizer->SetSizeHints(this);
}
