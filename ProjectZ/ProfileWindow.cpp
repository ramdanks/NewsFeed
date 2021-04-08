#include "ProfileWindow.h"
#include "ProfilePanel.h"
#include "Profile.h"
#include "Theme.h"
#include "Image.h"

ProfileWindow::ProfileWindow(wxWindow* parent)
	: wxScrolledWindow(parent, wxID_ANY)
{
	BuildGUI();
	this->SetCursor(wxCURSOR_HAND);
}

void ProfileWindow::BuildGUI()
{
	constexpr int height = 50;
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
		sProfile info;
		info.name = "Buzz Lightyear";
		info.bio = "To Beyond and Infinity!";
		info.picture = Image::GetBitmap(PROFILE_IMG);

		auto* pn = new ProfilePanel(info, this, -1, wxPoint(0, i * height), wxSize(width, height));
		sizer->Add(pn, 0, wxEXPAND);
	}

	this->SetSizer(sizer);
	sizer->SetSizeHints(this);
}
