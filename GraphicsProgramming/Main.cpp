#include "Defines.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
    auto errorType = ErrorType::SUCCESS;
    
    auto* pEngine = new Engine();
    if (pEngine != nullptr)
    {
        PROVE_RESULT(pEngine->Initialize())
        PROVE_RESULT(pEngine->Run())
        FINALIZE_DELETE(pEngine)
    }
    else
    {
        errorType = ErrorType::CREATE_ENGINE_FAILED;
        ErrorHandler::LogError("Cannot create engine. Engine is null. ", errorType);
        return static_cast<int>(errorType);
    }
    
    return static_cast<int>(errorType);
}