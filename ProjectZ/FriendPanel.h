#pragma once
#include <wx/wx.h>

struct sFriend
{
    wxString name, bio;
    wxBitmap picture;
};

class FriendPanel : public wxPanel
{
public:
	FriendPanel(const sFriend& info, wxWindow* parent, const wxWindowID& id,
                const wxPoint& point, const wxSize& size);

    void SetInfo(const sFriend& info);

private:
    void BuildGUI();
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLPress(wxMouseEvent& event);
    void OnMouseLRelease(wxMouseEvent& event);
    void OnMouseRClick(wxMouseEvent& event);
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);

    sFriend mInfo;
    wxStaticText* mName;
    wxStaticText* mBio;
    wxStaticBitmap* mPicture;
    bool mFocus;

    wxDECLARE_EVENT_TABLE();
};

