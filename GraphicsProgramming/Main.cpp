// The origin source code is from the SAE Institute Graphics Programming lecture (Marcus Schaal).
// It is adjusted, modified and extended by me(Felix Wahl) for a 3D Model Viewer.

#include "FileDataHandler.h"
#include "Defines.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
    auto errorType = ErrorType::SUCCESS;
    
    auto* pData = new DataManager();
    auto* pEngine = new Engine(pData);
    
    if (pEngine != nullptr)
    {
        PROVE_RESULT(pEngine->Initialize())
        PROVE_RESULT(pEngine->Run())
        FINALIZE_DELETE(pEngine)
        SAVE_DELETE(pData)
    }
    else
    {
        errorType = ErrorType::CREATE_ENGINE_FAILED;
        ErrorHandler::LogError("Cannot create engine. Engine is null. ", errorType, __FILE__, __LINE__);
        
        return static_cast<int>(errorType);
    }
    
    return static_cast<int>(errorType);
}