#include "Image.h"

std::array<wxBitmap, ImageId::COUNT> Image::sBitmap;

void Image::Fetch()
{
    sBitmap[PROFILE_IMG] = LoadImageFile("img/blank.png", wxBITMAP_TYPE_PNG);
}

wxBitmap& Image::GetImage(ImageId id)
{
    return sBitmap[id];
}

wxBitmap Image::LoadImageFile(const wxString& filepath, wxBitmapType type)
{
    wxBitmap bmp;
    bmp.LoadFile(filepath, type);
    return bmp;
}
