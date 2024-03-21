#include "ErrorHandler.h"
#include "Engine.h"

/// <summary>
/// @brief Initialize with std::unique_ptr instead of raw pointers.
/// This ensures automatic memory management and reduces the risk of memory leaks.
/// @return bool indicating whether the initialization was successful
/// </summary>
bool Engine::InitializeObjects()
{
    try
    {
        pViewport = std::make_unique<Viewport>(GLFW_MINOR_VERSION, GLFW_MAJOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_TITLE,  BLACK);
        pMaterial = std::make_unique<Material>(vertexShaderFileName, fragmentShaderFileName);
        pCamera = std::make_unique<Camera>();
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
        return static_cast<int>(message);
    }
    
    pViewport->Initialize();
    pMaterial->Initialize();
    pModel->Initialize();

    pViewport->SetMaterial(pMaterial.get());
    pViewport->SetCamera(pCamera.get());
    pMaterial->SetModel(pModel.get());
    
    return static_cast<int>(message);
}

int Engine::Run()
{
    if (pViewport)
    {
        while (!glfwWindowShouldClose(pViewport->GetWindow()))
        {
            pViewport->Update();
            pMaterial->Update(pCamera.get());
            
            pViewport->Draw();
            pMaterial->Draw();
            
            pModel->Draw(*pMaterial->GetModelShader());
            
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

void Engine::Finalize() const
{
    pViewport->Finalize();
    pMaterial->Finalize();
}
