#include "Application.h"
#include "Defines.h"
#include "Engine.h"


int Application::Run()
{
    if (pEngine)
    {
        PROVE_RESULT(pEngine->Initialize())
        PROVE_RESULT(pEngine->Run())
    }
    else
    {
        errorType = ErrorType::ENGINE_INIT_FAILED;
        ErrorHandler::LogError("Cannot initialize engine. Engine is null. ", errorType, __FILE__, __LINE__);
        
        return static_cast<int>(errorType);
    }

    return static_cast<int>(errorType);
}
