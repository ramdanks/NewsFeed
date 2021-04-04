#pragma once
#include <wx/wx.h>

class SystemBar : public wxPanel
{
public:
	SystemBar(wxWindow* parent);
	~SystemBar();

private:
	void BuildGUI();

    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLPress(wxMouseEvent& event);
    void OnMouseLRelease(wxMouseEvent& event);
    void OnMouseRClick(wxMouseEvent& event);

    bool m_dragging;
    int x, y;
    
    wxWindow* mParent;

    DECLARE_EVENT_TABLE();
};
