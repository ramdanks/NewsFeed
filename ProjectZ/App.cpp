#include "App.h"

wxIMPLEMENT_APP(App);

App::App()
    : mpFrameMain(nullptr)
{
}

App::~App()
{
}

bool App::OnInit()
{
    if (!mpFrameMain)
    {
        mpFrameMain = new FrameMain();
        mpFrameMain->Show();
    }
    return true;
}

int App::OnExit()
{
    return 0;
}