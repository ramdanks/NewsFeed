#include "SystemBar.h"
#include "Id.h"
#include <wx/hyperlink.h>

BEGIN_EVENT_TABLE(SystemBar, wxPanel)
EVT_MOTION(SystemBar::OnMouseMove)
EVT_LEFT_DOWN(SystemBar::OnMouseLPress)
EVT_LEFT_UP(SystemBar::OnMouseLRelease)
EVT_RIGHT_DOWN(SystemBar::OnMouseRClick)
EVT_BUTTON(ID_MINIMIZE_BTN, SystemBar::OnMinimizeBtn)
EVT_BUTTON(ID_MAXIMIZE_BTN, SystemBar::OnMaximizeBtn)
EVT_BUTTON(ID_CLOSE_BTN, SystemBar::OnCloseBtn)
END_EVENT_TABLE()

SystemBar::SystemBar(wxFrame* parent)
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

    mMinimize = new wxBitmapButton(this, ID_MINIMIZE_BTN, wxBITMAP_PNG(IMG_MINIMIZE));
    mMaximize = new wxBitmapButton(this, ID_MAXIMIZE_BTN, wxBITMAP_PNG(IMG_MAXIMIZE));
    mClose = new wxBitmapButton(this, ID_CLOSE_BTN, wxBITMAP_PNG(IMG_CLOSE));

    SetHyperlinkColour(friends);
    SetHyperlinkColour(teams);
    SetHyperlinkColour(chats);

    sizer->Add(friends, 0, wxCENTER | wxLEFT | wxRIGHT, 20);
    sizer->Add(teams, 0, wxCENTER | wxRIGHT, 20);
    sizer->Add(chats, 0, wxCENTER | wxRIGHT, 20);
    sizer->AddStretchSpacer();
    sizer->Add(mMinimize);
    sizer->Add(mMaximize);
    sizer->Add(mClose);

    this->SetSizer(sizer);
    sizer->SetSizeHints(this);
}

void SystemBar::OnMouseMove(wxMouseEvent& event)
{
    if (m_dragging)
    {
        wxPoint mouseOnScreen = wxGetMousePosition();
        if (mParent->IsMaximized())
        {
            auto prevSize = mParent->GetSize();
            ChangeMaximizeMode();
            auto restoreSize = mParent->GetSize();
            auto scale = (float) mouseOnScreen.x / prevSize.x;
            mParent->Move(mouseOnScreen);
            m_pos = wxPoint(restoreSize.x * scale, mouseOnScreen.y);
        }
        else
        {
            auto newpos = mouseOnScreen - m_pos;
            mParent->Move(newpos);
        }
    }
}

void SystemBar::OnMouseLPress(wxMouseEvent& event)
{
    CaptureMouse();
    m_pos = event.GetPosition();
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

void SystemBar::OnCloseBtn(wxCommandEvent& event)
{
    mParent->Close();
}

void SystemBar::OnMaximizeBtn(wxCommandEvent& event)
{
    ChangeMaximizeMode();
}

void SystemBar::OnMinimizeBtn(wxCommandEvent& event)
{
    mParent->Iconize();
}

void SystemBar::ChangeMaximizeMode()
{
    auto maximized = mParent->IsMaximized();
    if (maximized) mMaximize->SetBitmap(wxBITMAP_PNG(IMG_MAXIMIZE));
    else mMaximize->SetBitmap(wxBITMAP_PNG(IMG_MAXIMIZE_RESTORE));
    mParent->Maximize(!maximized);
}
