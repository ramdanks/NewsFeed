#pragma once
#include <wx/wx.h>

enum sPStatus
{
    MYACCOUNT, FOLLOWED, NONFOLLOWED
};

struct sProfile
{
    wxString username, displayname, bio;
    wxBitmap picture;
    sPStatus status = MYACCOUNT;
    int cbIndex = 0;
};