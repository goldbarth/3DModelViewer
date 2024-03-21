#include "Application.h"

void Application::Run() const
{
    pEngine->Initialize();
    pEngine->Run();
    pEngine->Finalize();
}
