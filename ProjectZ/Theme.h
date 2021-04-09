#pragma once
#include <wx/wx.h>
#include <wx/hyperlink.h>

#define CLR_CHAT_BACK             wxColour(60,60,60)
#define CLR_CHAT_FORE             wxColour(240,240,240)
#define CLR_NAV_BACK              wxColour(40,40,40)
#define CLR_NAV_FORE              wxColour(240,240,240)
#define CLR_LANDING_FORE          wxColour(230, 230, 230)
#define CLR_LANDING_BACK          wxColour(40, 40, 40)
#define CLR_ENTRY_BACK            wxColour(25, 25, 25)
#define CLR_ENTRY_FORE            wxColour(250, 250, 250)
#define CLR_SYSBAR_BACK           wxColour(30,30,30)
#define CLR_SYSBAR_FORE           wxColour(240,240,240)
#define CLR_PROFILE_BACK          wxColour(30,30,30)
#define CLR_PROFILE_FORE          wxColour(240,240,240)
#define CLR_FRIEND_IDLE_BACK      wxColour(40,40,40)
#define CLR_FRIEND_IDLE_FORE      wxColour(230,230,230)
#define CLR_FRIEND_FOCUS_BACK     wxColour(60,60,60)
#define CLR_FRIEND_FOCUS_FORE     wxColour(230,230,230)
#define CLR_FRIEND_BIO            wxColour(180,180,180)
#define CLR_CONTENT_TITLE_BACK    wxColour(25,25,25)
#define CLR_CONTENT_TITLE_FORE    wxColour(240,240,240)
#define CLR_FEED_HEADER_BACK      wxColour(30,30,50)
#define CLR_FEED_HEADER_FORE      wxColour(225,225,225)
#define CLR_FEED_TEXT_BACK        wxColour(40,40,40)
#define CLR_FEED_TEXT_FORE        wxColour(240,240,240)

#define FONT_PROFILE       wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Roboto")
#define FONT_FRIEND_NAME   wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial")
#define FONT_FRIEND_BIO    wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial")
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

