#pragma once
#include <wx/wx.h>
#include <wx/hyperlink.h>

#define CLR_CHAT_BACK      wxColour(50,50,50)
#define CLR_CHAT_FORE      wxColour(240,240,240)
#define CLR_NAV_BACK       wxColour(40,40,40)
#define CLR_NAV_FORE       wxColour(240,240,240)
#define CLR_LANDING_FORE   wxColour(230, 230, 230)
#define CLR_LANDING_BACK   wxColour(40, 40, 40)
#define CLR_ENTRY_BACK     wxColour(25, 25, 25)
#define CLR_ENTRY_FORE     wxColour(250, 250, 250)
#define CLR_SYSBAR_BACK    wxColour(30,30,30)
#define CLR_SYSBAR_FORE    wxColour(240,240,240)
#define CLR_PROFILE_BACK   wxColour(30,30,30)
#define CLR_PROFILE_FORE   wxColour(240,240,240)

#define FONT_PROFILE       wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Roboto")
#define FONT_ENTRY         wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Calibri")
#define FONT_TITLE         wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Roboto")

class Theme
{
private:
	Theme();

public:
	static void SetWindow(wxWindow* wnd, const wxColour& back, const wxColour& fore);
	static void SetHyperlink(wxGenericHyperlinkCtrl* link);
};

