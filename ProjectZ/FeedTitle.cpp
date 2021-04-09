#include "FeedTitle.h"
#include "Theme.h"

wxPanel* FeedTitle::mPanel;
wxStaticText* FeedTitle::mTitle;

void FeedTitle::Init(wxWindow* parent, wxSize size, wxString title)
{
	mPanel = new wxPanel(parent, -1, wxDefaultPosition, size);
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	Theme::SetWindow(mPanel, CLR_CONTENT_TITLE_BACK, CLR_CONTENT_TITLE_FORE);
	mTitle = new wxStaticText(mPanel, -1, title);
	sizer->Add(mTitle, 0, wxCENTER | wxLEFT | wxRIGHT, 15);
	mPanel->SetSizer(sizer);
}

void FeedTitle::SetTitle(wxString title)
{
	mTitle->SetLabel(title);
}

wxString FeedTitle::GetTitle()
{
	return mTitle->GetLabel();
}

wxPanel* FeedTitle::Get()
{
	return mPanel;
}
