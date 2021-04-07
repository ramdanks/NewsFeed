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

    mFrameMain = new FrameMain();
    mFrameMain->Show();

    auto* dashboard = new Dashboard(nullptr);
    dashboard->Show();

    PROFILE_END();
    return true;
}

int App::OnExit()
{
    return 0;
}