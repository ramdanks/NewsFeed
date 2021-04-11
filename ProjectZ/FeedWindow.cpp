#include "FeedWindow.h"

FeedWindow::FeedWindow(wxWindow* parent)
    : wxScrolledWindow(parent)
{
    BuildGUI();
}

bool FeedWindow::Add(const sFeed& feed)
{
    if (IsExist(feed))
        return false;

    auto* feedp = new FeedPanel(this, feed);
    mFeeds[feed.id] = feedp;

    mSizer->Add(feedp, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    mSizer->Layout();
    return true;
}

bool FeedWindow::Clear()
{
    if (mFeeds.empty())
        return false;
    mFeeds.clear();
    mSizer->Clear(true);
}

bool FeedWindow::Remove(int id)
{
    mFeeds.erase(id);
    return true;
}

bool FeedWindow::Remove(const sFeed& feed)
{
    mFeeds.erase(feed.id);
    return true;
}

bool FeedWindow::IsExist(int id)
{
    auto it = mFeeds.find(id);
    return it != mFeeds.end();
}

bool FeedWindow::IsExist(const sFeed& feed)
{
    auto it = mFeeds.find(feed.id);
    return it != mFeeds.end();
}

void FeedWindow::BuildGUI()
{
	constexpr int height = 50;
	constexpr int width = 200;
	constexpr int size = 30;

	constexpr int scrollUnitX = width / 10;
	constexpr int scrollUnitY = height / 10;

	constexpr int scaleUnitX = width / scrollUnitX;
	constexpr int scaleUnitY = size * height / scrollUnitY;

	SetScrollbars(scrollUnitX, scrollUnitY,
				  scaleUnitX, scaleUnitY,
				  0, 0);

	mSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mSizer);
}
