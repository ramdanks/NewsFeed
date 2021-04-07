#pragma once
#include <wx/wx.h>

class SystemBar : public wxPanel
{
public:
	SystemBar(wxFrame* parent);
	~SystemBar();

private:
	void BuildGUI();

    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLPress(wxMouseEvent& event);
    void OnMouseLRelease(wxMouseEvent& event);
    void OnMouseRClick(wxMouseEvent& event);

    void OnCloseBtn(wxCommandEvent& event);
    void OnMaximizeBtn(wxCommandEvent& event);
    void OnMinimizeBtn(wxCommandEvent& event);

    void ChangeMaximizeMode();

    bool m_dragging;
    wxPoint m_pos;
    
    wxFrame* mParent;
    wxBitmapButton* mClose, * mMaximize, * mMinimize;
    DECLARE_EVENT_TABLE();
};
