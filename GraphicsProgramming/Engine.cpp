#include "ErrorHandler.h"
#include "Defines.h"
#include "Engine.h"

const std::string Engine::WINDOW_TITLE = "Glodbarth Engine 1.0";

const Color Engine::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color Engine::TURQUOISE(0.0f, 0.5f, 0.5f, 1.0f);
const Color Engine::DARK_GRAY(0.25f, 0.25f, 0.25f, 1.0f);
const Color Engine::LIGHT_GRAY(0.75f, 0.75f, 0.75f, 1.0f);

int Engine::Initialize()
{
    if(pData == nullptr) return static_cast<int>(ErrorType::DATA_MANAGER_INIT_FAILED);
    const std::string vertexShaderSource = pData->ReadFile("Resource Files/Shader/DefaultVertex.glsl");
    if(pData == nullptr) return static_cast<int>(ErrorType::DATA_MANAGER_INIT_FAILED);
    const std::string fragmentShaderSource = pData->ReadFile("Resource Files/Shader/DefaultFragment.glsl");
    
    // Create viewport (Window)
    INIT_VIEWPORT(pViewport)
    if(pViewport != nullptr) PROVE_RESULT(pViewport->Initialize())

    // Create material (Shaders)
    INIT_MATERIAL(pMaterial, vertexShaderSource.c_str(), fragmentShaderSource.c_str())
    if(pMaterial != nullptr) PROVE_RESULT(pMaterial->Initialize())

    // Create mesh (Geometry)
    INIT_MESH(pMesh, pVertices)
    if(pMesh != nullptr) PROVE_RESULT(pMesh->Initialize())
    
    return static_cast<int>(errorType);
}

int Engine::Run()
{
    if (pViewport != nullptr)
    {
        while (!glfwWindowShouldClose(pViewport->getWindow()))
        {
            if (pViewport != nullptr) PROVE_RESULT(pViewport->Update())
            if (pMaterial != nullptr) PROVE_RESULT(pMaterial->Update())
            if (pMesh != nullptr) PROVE_RESULT(pMesh->Update())
            
            if (pViewport != nullptr) PROVE_RESULT(pViewport->Draw())
            if (pMaterial != nullptr) PROVE_RESULT(pMaterial->Draw())
            if (pMesh != nullptr) PROVE_RESULT(pMesh->Draw())
            
            if (pViewport != nullptr) PROVE_RESULT(pViewport->LateDraw())
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
    FINALIZE_DELETE(pMaterial)
    FINALIZE_DELETE(pMesh)
}
