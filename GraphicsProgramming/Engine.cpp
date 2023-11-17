#include <glm/gtc/constants.hpp>

#include "ErrorHandler.h"
#include "Defines.h"
#include "Engine.h"


const std::string Engine::WINDOW_TITLE = "Glodbarth Engine 1.0";

// Shader values

const char* Engine::pAmbientVertexShaderName = "AmbientVertex.glsl";
const char* Engine::pAmbientFragmentShaderName = "AmbientFragment.glsl";
const char* Engine::pDefaultVertexShaderName = "DefaultVertex.glsl";
const char* Engine::pDefaultFragmentShaderName = "DefaultFragment.glsl";

// Camera values

const glm::vec3 Engine::CAMERA_POSITION = glm::vec3(0.0f, 0.0f, 250.0f);
const glm::vec3 Engine::CAMERA_ORIENTATION = glm::vec3(0.0f, 0.0f, -0.5f);
const glm::vec3 Engine::CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);

// Input values

const glm::vec3 Engine::FORWARD_INPUT = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Engine::BACKWARD_INPUT = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 Engine::LEFT_INPUT = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 Engine::RIGHT_INPUT = glm::vec3(0.0f, 0.0f, -1.0f);

// Colors

const Color Engine::GOLD(1.0f, 0.84f, 0.0f, 1.0f);
const Color Engine::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color Engine::TURQUOISE(0.0f, 0.5f, 0.5f, 1.0f);
const Color Engine::DARK_GRAY(0.25f, 0.25f, 0.25f, 1.0f);
const Color Engine::LIGHT_GRAY(0.75f, 0.75f, 0.75f, 1.0f);


int Engine::Initialize()
{
    // Initialize objects
    if (pCamera == nullptr) pCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POSITION, CAMERA_ORIENTATION, CAMERA_UP);
    if (pViewport == nullptr) pViewport = new Viewport(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_TITLE, TURQUOISE);
    if (pMaterial == nullptr) pMaterial = new Material(pData, pData->GetShaderFolderPath(), pDefaultVertexShaderName, pDefaultFragmentShaderName);
    // if (pAmbient == nullptr) pAmbient = new Ambient(pData, pData->GetShaderFolderPath(), pAmbientVertexShaderName, pAmbientFragmentShaderName);
    if (pMesh == nullptr) pMesh = new Mesh(vertices, indices, textures);

    if (pViewport != nullptr && pCamera != nullptr)
    {
        pViewport->SetForwardInput([&]() { pCamera->TranslatePosition(FORWARD_INPUT); });
        pViewport->SetBackwardInput([&]() { pCamera->TranslatePosition(BACKWARD_INPUT); });
        pViewport->SetLeftInput([&]() { pCamera->TranslatePosition(LEFT_INPUT); });
        pViewport->SetRightInput([&]() { pCamera->TranslatePosition(RIGHT_INPUT); });
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
            
            if (pCamera != nullptr) pCamera->SetCameraData(CameraData{ DEFAULT_CAMERA_FOV, DEFAULT_CAMERA_NEAR, DEFAULT_CAMERA_FAR, pMaterial->GetShaderProgram(), CAMERA_UNIFORM_NAME.c_str()} );
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
    FINALIZE_DELETE(pCamera)
}
