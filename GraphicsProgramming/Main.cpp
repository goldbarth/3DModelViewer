#include "Defines.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
    auto* pEngine = new Engine();
    if (pEngine == nullptr)
    {
        PROVE_RESULT(pEngine->Initialize())
        PROVE_RESULT(pEngine->Run())
        FINALIZE_DELETE(pEngine)
    }
    else
    {
        ErrorHandler::LogError("Cannot create engine. Engine is null. ", ErrorType::CREATE_ENGINE_FAILED);
        return static_cast<int>(ErrorType::CREATE_ENGINE_FAILED);
    }
    
    return static_cast<int>(ErrorType::SUCCESS);
}
