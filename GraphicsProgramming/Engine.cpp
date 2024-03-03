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
        pViewport = std::make_unique<Viewport>(GLFW_MINOR_VERSION, GLFW_MAJOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_TITLE, TURQUOISE);
        pMaterial = std::make_unique<Material>();
        pMesh = std::make_unique<Mesh>(vertices, indices);
        
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
    pMesh->Initialize();
    
    return static_cast<int>(message);
}

int Engine::Update()
{
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
            pMesh->Draw();
            
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

void Engine::Finalize()
{
    pViewport->Finalize();
    pMesh->Finalize();
    pMaterial->Finalize();
}
