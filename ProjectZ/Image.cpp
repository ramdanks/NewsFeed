#include "Image.h"

std::array<wxBitmap, ImageId::COUNT> Image::sBitmap;

void Image::Fetch()
{
    sBitmap[PROFILE_IMG] = LoadImageFile("img/blank.png", wxBITMAP_TYPE_PNG);
}

wxImage Image::GetImage(ImageId id)
{
    return sBitmap[id].ConvertToImage();
}

wxImage Image::GetImageScale(ImageId id, int w, int h)
{
    auto img = sBitmap[id].ConvertToImage();
    if (img.GetWidth() != w || img.GetHeight() != h)
        img.Rescale(35, 35);
    return img;
}

wxBitmap Image::LoadImageFile(const wxString& filepath, wxBitmapType type)
{
    wxBitmap bmp;
    bmp.LoadFile(filepath, type);
    return bmp;
}
