#pragma once
#include <wx/wx.h>
#include <array>
#include "ImageId.h"

class Image
{
public:
	Image() = delete;
	static void Fetch();

	static wxImage GetImage(ImageId id);
	static wxBitmap GetBitmap(ImageId id);
	static void SetBitmapScale(wxBitmap& bitmap, int w, int h);
	static void SetImageScale(wxImage& image, int w, int h);

private:
	static std::array<wxBitmap, ImageId::COUNT> sBitmap;
	static wxBitmap LoadImageFile(const wxString& filepath, wxBitmapType type);
};

