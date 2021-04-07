#pragma once
#include <wx/wx.h>
#include <array>
#include "ImageId.h"

class Image
{
public:
	Image() = delete;
	static void Fetch();
	static wxBitmap& GetImage(ImageId id);

private:
	static std::array<wxBitmap, ImageId::COUNT> sBitmap;
	static wxBitmap LoadImageFile(const wxString& filepath, wxBitmapType type);
};

