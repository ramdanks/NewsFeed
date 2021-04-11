#pragma once
#include <wx/wx.h>
#include "Profile.h"

wxDECLARE_EVENT(EVT_PP_IMG, wxCommandEvent);
wxDECLARE_EVENT(EVT_PP_PRESS, wxCommandEvent);

class ProfilePanel : public wxPanel
{
public:
	ProfilePanel(const sProfile& info, wxWindow* parent, const wxWindowID& id,
                const wxPoint& point, const wxSize& size);

    void SetInfo(const sProfile& info);

private:
    void BuildGUI();
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLPress(wxMouseEvent& event);
    void OnMouseLRelease(wxMouseEvent& event);
    void OnMouseRClick(wxMouseEvent& event);
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);

    sProfile mInfo;
    wxWindow* mParent;
    wxStaticText* mName;
    wxStaticText* mBio;
    wxStaticBitmap* mPicture;
    bool mFocus;

    wxDECLARE_EVENT_TABLE();
};

