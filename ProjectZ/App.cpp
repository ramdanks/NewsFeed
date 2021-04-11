#include "App.h"
#include "Instrumentator.h"
#include "Dashboard.h"

wxIMPLEMENT_APP(App);

App::App()
{
    wxInitAllImageHandlers();
}

App::~App()
{
}

bool App::OnInit()
{
    PROFILE_BEGIN("App Init", "Profiling/Init.json");

    wxInitAllImageHandlers();

    mFrameMain = new FrameMain();
    mFrameMain->Show();

    PROFILE_END();
    return true;
}

int App::OnExit()
{
    return 0;
}