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
	static wxImage GetImageScale(ImageId id, int w, int h);

private:
	static std::array<wxBitmap, ImageId::COUNT> sBitmap;
	static wxBitmap LoadImageFile(const wxString& filepath, wxBitmapType type);
};

