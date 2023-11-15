#include <glm/gtc/constants.hpp>

#include "ErrorHandler.h"
#include "Defines.h"
#include "Engine.h"


const std::string Engine::WINDOW_TITLE = "Glodbarth Engine 1.0";

const Color Engine::GOLD(1.0f, 0.84f, 0.0f, 1.0f); //(1.0f, 0.5f, 0.2f, 1.0f)
const Color Engine::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color Engine::TURQUOISE(0.0f, 0.5f, 0.5f, 1.0f);
const Color Engine::DARK_GRAY(0.25f, 0.25f, 0.25f, 1.0f);
const Color Engine::LIGHT_GRAY(0.75f, 0.75f, 0.75f, 1.0f);

int Engine::Initialize()
{
    // Set shader sources. Read from files.
    if(pData == nullptr) return static_cast<int>(ErrorType::DATA_MANAGER_INIT_FAILED);
    const std::string ambientVertexShaderSource = pData->ReadFile("Resource Files/Shader/AmbientVertex.glsl");
    if(pData == nullptr) return static_cast<int>(ErrorType::DATA_MANAGER_INIT_FAILED);
    const std::string ambientFragmentShaderSource = pData->ReadFile("Resource Files/Shader/AmbientFragment.glsl");
    
        
    // Initialize objects
    INIT_CAMERA(pCamera, WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f))
    INIT_VIEWPORT(pViewport)
    INIT_MATERIAL(pMaterial, pData, "Resource Files/Shader/DefaultVertex.glsl", "Resource Files/Shader/DefaultFragment.glsl")
    // INIT_AMBIENT(pAmbient, pData, "Resource Files/Shader/AmbientVertex.glsl", "Resource Files/Shader/AmbientFragment.glsl")
    INIT_MESH(pMesh, vertices, indices)

    if (pViewport != nullptr && pCamera != nullptr)
    {
        forwardInput = [&]() {pCamera->TranslatePosition(glm::vec3(1.0f, 0.0f, 0.0f));};
        backwardInput = [&]() {pCamera->TranslatePosition(glm::vec3(-1.0f, 0.0f, 0.0f));};
        leftInput = [&]() {pCamera->TranslatePosition(glm::vec3(0.0f, 0.0f, 1.0f));};
        rightInput = [&]() {pCamera->TranslatePosition(glm::vec3(0.0f, 0.0f, -1.0f));};
    }
    
        
    
    if(pViewport != nullptr) PROVE_RESULT(pViewport->Initialize())
    if(pMaterial != nullptr) PROVE_RESULT(pMaterial->Initialize())
    // if (pAmbient != nullptr) pAmbient->SetLightColor(glm::vec3(0.5f, 0.5f, 0.5f));
    // if(pAmbient != nullptr) PROVE_RESULT(pAmbient->Initialize())
    if(pMesh != nullptr) PROVE_RESULT(pMesh->Initialize())
    
    return static_cast<int>(errorType);
}

int Engine::Run()
{
    if (pViewport != nullptr)
    {
        while (!glfwWindowShouldClose(pViewport->GetWindow()))
        {
            if (pViewport != nullptr) PROVE_RESULT(pViewport->Update())
            if (pMaterial != nullptr) PROVE_RESULT(pMaterial->Update())
            // if(pAmbient != nullptr) PROVE_RESULT(pAmbient->Update())
            if (pMesh != nullptr) PROVE_RESULT(pMesh->Update())
            
            if (pCamera != nullptr) pCamera->SetCameraData(CameraData{0.45f, 0.1f, 100.0f, pMaterial->GetShaderProgram(), "cameraMatrix"});
            if (pCamera != nullptr) PROVE_RESULT(pCamera->Update())
            
            if (pViewport != nullptr) PROVE_RESULT(pViewport->Draw())
            if (pMaterial != nullptr) PROVE_RESULT(pMaterial->Draw())
            // if(pAmbient != nullptr) PROVE_RESULT(pAmbient->Draw())
            if (pMesh != nullptr) PROVE_RESULT(pMesh->Draw())
            
            if (pViewport != nullptr) PROVE_RESULT(pViewport->LateDraw())
       }
    }
    else
    {
        errorType = ErrorType::RUN_VIEWPORT_FAILED;
        ErrorHandler::LogError("Cannot run application. Viewport is null.", errorType, __FILE__, __LINE__);
        return static_cast<int>(errorType);
    }
    
    return static_cast<int>(errorType);
}

void Engine::Finalize()
{
    FINALIZE_DELETE(pMesh)
    // FINALIZE_DELETE(pAmbient)
    FINALIZE_DELETE(pMaterial)
    FINALIZE_DELETE(pViewport)
}
