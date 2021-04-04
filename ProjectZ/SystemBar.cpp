#include "SystemBar.h"
#include <wx/hyperlink.h>

BEGIN_EVENT_TABLE(SystemBar, wxPanel)
EVT_MOTION(SystemBar::OnMouseMove)
EVT_LEFT_DOWN(SystemBar::OnMouseLPress)
EVT_LEFT_UP(SystemBar::OnMouseLRelease)
EVT_RIGHT_DOWN(SystemBar::OnMouseRClick)
END_EVENT_TABLE()

SystemBar::SystemBar(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200,30)),
    mParent(parent)
{
    BuildGUI();
}

SystemBar::~SystemBar()
{
}

void SystemBar::BuildGUI()
{
    auto SetHyperlinkColour = [](wxGenericHyperlinkCtrl* link)
    {
        link->SetNormalColour(wxColour(255, 255, 255));
        link->SetHoverColour(wxColour(52, 180, 240));
        link->SetVisitedColour(wxColour(255, 255, 255));
    };

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    auto* friends = new wxGenericHyperlinkCtrl(this, -1, "Friends", "");
    auto* teams = new wxGenericHyperlinkCtrl(this, -1, "Teams", "");
    auto* chats = new wxGenericHyperlinkCtrl(this, -1, "Chats", "");

    auto* minimizeBtn = new wxButton(this, -1);
    auto* maximizeBtn = new wxButton(this, -1);
    auto* closeBtn = new wxButton(this, -1);

    SetHyperlinkColour(friends);
    SetHyperlinkColour(teams);
    SetHyperlinkColour(chats);

    sizer->Add(friends, 0, wxCENTER | wxLEFT | wxRIGHT, 20);
    sizer->Add(teams, 0, wxCENTER | wxRIGHT, 20);
    sizer->Add(chats, 0, wxCENTER | wxRIGHT, 20);
    sizer->AddStretchSpacer();
    sizer->Add(minimizeBtn, 0, wxCENTER | wxRIGHT, 10);
    sizer->Add(maximizeBtn, 0, wxCENTER | wxRIGHT, 10);
    sizer->Add(closeBtn, 0, wxCENTER | wxRIGHT, 10);

    this->SetSizer(sizer);
}

void SystemBar::OnMouseMove(wxMouseEvent& event)
{
    if (m_dragging)
    {
        wxPoint mouseOnScreen = wxGetMousePosition();
        int newx = mouseOnScreen.x - x;
        int newy = mouseOnScreen.y - y;
        mParent->Move(newx, newy);
    }
}

void SystemBar::OnMouseLPress(wxMouseEvent& event)
{
    CaptureMouse();
    x = event.GetX();
    y = event.GetY();
    m_dragging = true;
}

void SystemBar::OnMouseLRelease(wxMouseEvent& event)
{
    ReleaseMouse();
    m_dragging = false;
}

void SystemBar::OnMouseRClick(wxMouseEvent& event)
{
}
