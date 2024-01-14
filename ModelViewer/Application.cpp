#include "Application.h"
#include "Defines.h"
#include "Engine.h"


int Application::Run()
{
    if (pEngine)
    {
        pEngine->Initialize();
        pEngine->Run();
    }
    else
    {
        errorType = MessageType::ENGINE_INIT_FAILED;
        ErrorHandler::LogError("Cannot initialize engine. Engine is null. ", errorType, __FILE__, __LINE__);
        
        return static_cast<int>(errorType);
    }

    return static_cast<int>(errorType);
}
