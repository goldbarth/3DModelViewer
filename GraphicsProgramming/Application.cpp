#include "FileDataHandler.h"
#include "Application.h"
#include "Defines.h"
#include "Engine.h"


int Application::Run()
{
    if (pEngine != nullptr)
    {
        PROVE_RESULT(pEngine->Initialize())
        PROVE_RESULT(pEngine->Run())
        FINALIZE_DELETE(pEngine)
        SAVE_DELETE(pData)
    }
    else
    {
        errorType = ErrorType::ENGINE_INIT_FAILED;
        ErrorHandler::LogError("Cannot initialize engine. Engine is null. ", errorType, __FILE__, __LINE__);
        
        return static_cast<int>(errorType);
    }

    return static_cast<int>(errorType);
}
