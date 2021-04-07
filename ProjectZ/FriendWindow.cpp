#include "FriendWindow.h"
#include "FriendPanel.h"
#include "Theme.h"

FriendWindow::FriendWindow(wxWindow* parent)
	: wxScrolledWindow(parent, wxID_ANY)
{
	BuildGUI();
}

void FriendWindow::BuildGUI()
{
	constexpr int height = 40;
	constexpr int width = 100;
	constexpr int size = 30;

	constexpr int scrollUnitX = width / 2;
	constexpr int scrollUnitY = height / 2;

	constexpr int scaleUnitX = width / scrollUnitX;
	constexpr int scaleUnitY = size * height / scrollUnitY;

	SetScrollbars(scrollUnitX, scrollUnitY,
				  scaleUnitX, scaleUnitY,
				  0, 0);

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	
	for (int i = 0; i < size; i++)
	{
		auto* pn = new FriendPanel(this, -1, wxPoint(0, i * height), wxSize(width, height));
		new wxStaticText(pn, -1, "Unknown User");
		sizer->Add(pn, 0, wxEXPAND);
	}

	this->SetSizer(sizer);
	sizer->SetSizeHints(this);

}
