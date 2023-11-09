#include "ErrorHandler.h"
#include "Defines.h"
#include "Engine.h"

int Engine::Initialize()
{
    INIT_VIEWPORT(pViewport)
    if(pViewport != nullptr) PROVE_RESULT(pViewport->Initialize())
    return static_cast<int>(errorType);
}

int Engine::Run()
{
    if (pViewport != nullptr)
    {
        while (!glfwWindowShouldClose(pViewport->getWindow()))
        {
            PROVE_RESULT(pViewport->Update())
            PROVE_RESULT(pViewport->Draw())
       }
    }
    else
    {
        errorType = ErrorType::RUN_VIEWPORT_FAILED;
        ErrorHandler::LogError("Cannot run application. Viewport is null.", errorType);
        return static_cast<int>(errorType);
    }
    
    return static_cast<int>(errorType);
}

void Engine::Finalize()
{
    FINALIZE_DELETE(pViewport)
}
