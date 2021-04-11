#include "FeedPanel.h"
#include "Theme.h"
#include "Image.h"

FeedPanel::FeedPanel(wxWindow* parent)
	: wxPanel(parent)
{
	sFeed feed = {-1, "", "", ""};
	BuildGUI(feed);
}

FeedPanel::FeedPanel(wxWindow* parent, const sFeed& feed)
	: wxPanel(parent)
{
	BuildGUI(feed);
}

void FeedPanel::SetDate(const wxString& date)
{
	mDate->SetLabel(date);
}

void FeedPanel::SetText(const wxString& text)
{
	mText->SetLabel(text);
}

void FeedPanel::SetFlag(const wxString& flag)
{
	mFlag->SetLabel(flag);
}

void FeedPanel::SetFeed(const sFeed& feed)
{
	SetDate(feed.date);
	SetText(feed.text);
	SetFlag(feed.flag);
}

void FeedPanel::BuildGUI(const sFeed& feed)
{
	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto* sizerH = new wxBoxSizer(wxHORIZONTAL);

	mHeader = new wxPanel(this, -1, wxPoint(0,0), wxSize(200, 30));
	Theme::SetWindow(mHeader, CLR_FEED_HEADER_BACK, CLR_FEED_HEADER_FORE);

	auto fimg = Image::GetImage(FLAG_PNG);
	fimg.Rescale(15, 15);
	auto* fBmp = new wxStaticBitmap(mHeader, -1, wxBitmap(fimg));
	mFlag = new wxStaticText(mHeader, -1, feed.flag);
	mDate = new wxStaticText(mHeader, -1, feed.date);

	sizerH->AddSpacer(10);
	sizerH->Add(fBmp, 0, wxCENTER);
	sizerH->AddSpacer(5);
	sizerH->Add(mFlag, 0, wxCENTER);
	sizerH->AddStretchSpacer();
	sizerH->Add(mDate, 0, wxCENTER);
	sizerH->AddSpacer(10);
	mHeader->SetSizer(sizerH);

	mText = new wxTextCtrl(this, -1, feed.text);
	mText->SetExtraStyle(wxTE_MULTILINE | wxNO_BORDER | wxTE_READONLY);
	Theme::SetWindow(mText, CLR_FEED_TEXT_BACK, CLR_FEED_TEXT_FORE);

	sizer->Add(mHeader, 0, wxEXPAND);
	sizer->Add(mText, 0, wxEXPAND);
	this->SetSizer(sizer);
}
