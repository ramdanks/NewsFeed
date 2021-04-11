#include "SettingDialog.h"
#include "DBRequest.h"
#include "Id.h"
#include "UserPanel.h"

BEGIN_EVENT_TABLE(SettingDialog, wxDialog)
EVT_BUTTON(ID_SETTING_DISPLAYNAME, SettingDialog::OnSetDisplaynameBtn)
EVT_BUTTON(ID_SETTING_BIO, SettingDialog::OnSetBioBtn)
EVT_BUTTON(ID_SETTING_LOGOUT, SettingDialog::OnLogoutBtn)
END_EVENT_TABLE()

SettingDialog::SettingDialog(wxWindow* parent)
	: wxDialog(parent, -1, "Setting", wxDefaultPosition, wxSize(200,150))
{
	auto sizer = new wxBoxSizer(wxVERTICAL);

	auto* btn1 = new wxButton(this, ID_SETTING_DISPLAYNAME, "Set Display Name");
	auto* btn2 = new wxButton(this, ID_SETTING_BIO, "Set Bio");
	auto* btn3 = new wxButton(this, ID_SETTING_LOGOUT, "Logout");

	sizer->Add(btn1, 1, wxEXPAND);
	sizer->Add(btn2, 1, wxEXPAND);
	sizer->Add(btn3, 1, wxEXPAND);

	this->SetSizer(sizer);
}

void SettingDialog::OnLogoutBtn(wxCommandEvent& event)
{
	EndModal(MODAL_LOGOUT);
}

void SettingDialog::OnSetBioBtn(wxCommandEvent& event)
{
	wxTextEntryDialog ted(this, "Insert Bio:", "Set Bio");
	if (ted.ShowModal() == wxID_OK)
	{
		try
		{
			wxString bio = ted.GetValue();

			if (bio.empty())
				throw "Please insert bio!";

			if(!DBRequest::SetBio(bio.ToStdString(), UserPanel::GetUser().username.ToStdString()))
				throw "Oops, cannot commit to the database";

			UserPanel::SetBio(bio);
		}
		catch (const char* msg)
		{
			wxMessageBox(msg, "Set Bio", wxICON_WARNING);
		}
	}
}

void SettingDialog::OnSetDisplaynameBtn(wxCommandEvent& event)
{
	wxTextEntryDialog ted(this, "Insert Display Name:", "Set Display Name");
	if (ted.ShowModal() == wxID_OK)
	{
		try
		{
			wxString name = ted.GetValue();

			if (name.empty())
				throw "Please insert bio!";

			if (!DBRequest::SetDisplayName(name.ToStdString(), UserPanel::GetUser().username.ToStdString()))
				throw "Oops, cannot commit to the database";

			UserPanel::SetDisplayname(name);
		}
		catch (const char* msg)
		{
			wxMessageBox(msg, "Set Display Name", wxICON_WARNING);
		}
	}
}
