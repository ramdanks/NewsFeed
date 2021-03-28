#include "App.h"
#include "Instrumentator.h"

wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    PROFILE_BEGIN("App Init", "Profiling/Init.json");

    {
        PROFILE_SCOPE("Create FrameMain");
        mpFrameMain = new FrameMain();
        mpFrameMain->Show();
    }

    PROFILE_END();
    return true;
}

int App::OnExit()
{
    return 0;
}