#pragma once
#include <wx/wx.h>

class FriendPanel : public wxPanel
{
public:
	FriendPanel(wxWindow* parent, const wxWindowID& id,
                const wxPoint& point, const wxSize& size);

private:
    void BuildGUI();
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLPress(wxMouseEvent& event);
    void OnMouseLRelease(wxMouseEvent& event);
    void OnMouseRClick(wxMouseEvent& event);
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);

    bool mFocus;

    wxDECLARE_EVENT_TABLE();
};

