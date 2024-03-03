#include "ErrorHandler.h"
#include "Engine.h"

/// <summary>
/// Initialize with std::unique_ptr instead of raw pointers. This ensures automatic memory management and reduces the risk of memory leaks.
/// Also, reducing of repetitive nullpointer checks in the run loop -> better performance.
/// </summary>
bool Engine::InitializeObjects()
{
    try
    {
        pViewport = std::make_unique<Viewport>(GLFW_MINOR_VERSION, GLFW_MAJOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_TITLE,  BLACK);
        pMaterial = std::make_unique<Material>();
        pModel = std::make_unique<Model>(absoluteModelPath);
        
        return true;
    }
    catch (const std::exception& e)
    {
        ErrorHandler::LogError(e.what(), __FILE__, __LINE__);
        return false;
    }
}

int Engine::Initialize()
{
    if (!InitializeObjects())
    {
        message = MessageType::ENGINE_INIT_FAILED;
        ErrorHandler::LogError(message, __FILE__, __LINE__);
    }
    
    pViewport->Initialize();
    pMaterial->Initialize();
    pModel->Initialize();
    
    return static_cast<int>(message);
}

int Engine::Run()
{
    if (pViewport)
    {
        while (!glfwWindowShouldClose(pViewport->GetWindow()))
        {
            pViewport->Update();
            pViewport->Draw();
            
            pMaterial->Draw();
            pModel->Draw(*pMaterial->GetShader());
            
            pViewport->LateDraw();
       }
    }
    else
    {
        message = MessageType::RUN_VIEWPORT_FAILED;
        ErrorHandler::LogError(message, __FILE__, __LINE__);
        return static_cast<int>(message);
    }
    
    return static_cast<int>(message);
}

int Engine::Draw()
{
    return static_cast<int>(message);
}

void Engine::Finalize() const
{
    pViewport->Finalize();
    pMaterial->Finalize();
}
