#include "Theme.h"

void Theme::SetWindow(wxWindow* wnd, const wxColour& back, const wxColour& fore)
{
	wnd->SetBackgroundColour(back);
	wnd->SetForegroundColour(fore);
}

void Theme::SetHyperlink(wxGenericHyperlinkCtrl* link)
{
	link->SetNormalColour(wxColour(255, 255, 255));
	link->SetHoverColour(wxColour(52, 180, 240));
	link->SetVisitedColour(wxColour(255, 255, 255));
}