#include "Image.h"

std::array<wxBitmap, ImageId::COUNT> Image::sBitmap;

void Image::Fetch()
{
    sBitmap[PROFILE_IMG] = LoadImageFile("img/blank.png", wxBITMAP_TYPE_PNG);
    sBitmap[FLAG_PNG] = LoadImageFile("img/flag.png", wxBITMAP_TYPE_PNG);
}

wxImage Image::GetImage(ImageId id)
{
    return sBitmap[id].ConvertToImage();
}

wxBitmap Image::GetBitmap(ImageId id)
{
    return sBitmap[id];
}

void Image::SetBitmapScale(wxBitmap& bitmap, int w, int h)
{
    auto img = bitmap.ConvertToImage();
    SetImageScale(img, w, h);
    bitmap = wxBitmap(img);
}

void Image::SetImageScale(wxImage& image, int w, int h)
{
    if (image.GetWidth() != w || image.GetHeight() != h)
        image.Rescale(35, 35);
}

wxBitmap Image::LoadImageFile(const wxString& filepath, wxBitmapType type)
{
    wxBitmap bmp;
    bmp.LoadFile(filepath, type);
    return bmp;
}