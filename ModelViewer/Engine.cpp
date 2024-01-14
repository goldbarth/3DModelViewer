﻿#include "ErrorHandler.h"
#include "Defines.h"
#include "Engine.h"

const std::string Engine::WINDOW_TITLE = "Glodbarth Engine 1.0";

// GLFW values (versions)

const int Engine::GLFW_MAJOR_VERSION = 3;
const int Engine::GLFW_MINOR_VERSION = 3;

// Window values

const int Engine::WINDOW_WIDTH = 1920;
const int Engine::WINDOW_HEIGHT = 1080;
const int Engine::WINDOW_OFFSET_X = 0;
const int Engine::WINDOW_OFFSET_Y = 0;

// Shader values

const char* Engine::pAmbientVertexShaderName = "AmbientVertex.glsl";
const char* Engine::pAmbientFragmentShaderName = "AmbientFragment.glsl";
const char* Engine::pDefaultVertexShaderName = "DefaultVertex.glsl";
const char* Engine::pDefaultFragmentShaderName = "DefaultFragment.glsl";

// Camera values

const std::string Engine::CAMERA_UNIFORM_NAME = "projectionViewMatrix";

const glm::vec3 Engine::CAMERA_POSITION = glm::vec3(0.0f, 0.0f, 250.0f);
const glm::vec3 Engine::CAMERA_ORIENTATION = glm::vec3(0.0f, 0.0f, -0.5f);
const glm::vec3 Engine::CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);

const float Engine::DEFAULT_CAMERA_FOV_DEGREE = 0.45f;
const float Engine::DEFAULT_CAMERA_NEAR = 0.1f;
const float Engine::DEFAULT_CAMERA_FAR = 1000.0f;

// Input values

const glm::vec3 Engine::FORWARD_INPUT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 Engine::BACKWARD_INPUT = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 Engine::LEFT_INPUT = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 Engine::RIGHT_INPUT = glm::vec3(1.0f, 0.0f, 0.0f);

// Colors

const Color Engine::GOLD(1.0f, 0.84f, 0.0f, 1.0f);
const Color Engine::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color Engine::TURQUOISE(0.0f, 0.5f, 0.5f, 1.0f);
const Color Engine::DARK_GRAY(0.25f, 0.25f, 0.25f, 1.0f);
const Color Engine::LIGHT_GRAY(0.75f, 0.75f, 0.75f, 1.0f);

const CameraData& Engine::GetDefaultCameraData() const
{
    static CameraData defaultCameraData = {
        DEFAULT_CAMERA_FOV_DEGREE, 
        DEFAULT_CAMERA_NEAR,
        DEFAULT_CAMERA_FAR, 
        pMaterial->GetShaderProgram(),
        CAMERA_UNIFORM_NAME.c_str()
    };
    return defaultCameraData;
}

/// <summary>
/// Initialize with std::unique_ptr instead of raw pointers. This ensures automatic memory management and reduces the risk of memory leaks.
/// Also, reducing of repetitive nullpointer checks in the run loop -> better performance.
/// </summary>
bool Engine::InitializeObjects()
{
    try
    {
        pCamera = std::make_unique<Camera>(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_POSITION, CAMERA_ORIENTATION, CAMERA_UP);
        pViewport = std::make_unique<Viewport>(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSET_X, WINDOW_OFFSET_Y, WINDOW_TITLE, TURQUOISE);
        pMaterial = std::make_unique<Material>(std::move(pData), pData->GetShaderFolderPath(), pDefaultVertexShaderName, pDefaultFragmentShaderName);
        //pAmbient = std::make_unique<Ambient>(std::move(pData), pData->GetShaderFolderPath(), pAmbientVertexShaderName, pAmbientFragmentShaderName);
        pMesh = std::make_unique<Mesh>(vertices, indices, textures);
        
        return true;
    }
    catch (const std::exception& e)
    {
        ErrorHandler::LogError(e.what());
        return false;
    }
}

int Engine::Initialize()
{
    if (!InitializeObjects())
    {
        errorType = MessageType::ENGINE_INIT_FAILED;
        ErrorHandler::LogError(errorType, __FILE__, __LINE__);
        return static_cast<int>(errorType);
    }
    
    // Set input callbacks
    pViewport->SetForwardInput([&]() { pCamera->TranslatePosition(FORWARD_INPUT); });
    pViewport->SetBackwardInput([&]() { pCamera->TranslatePosition(BACKWARD_INPUT); });
    pViewport->SetLeftInput([&]() { pCamera->TranslatePosition(LEFT_INPUT); });
    pViewport->SetRightInput([&]() { pCamera->TranslatePosition(RIGHT_INPUT); });

    // Initialize objects
    pViewport->Initialize();
    pMaterial->Initialize();
    // pAmbient->SetLightColor(glm::vec3(0.5f, 0.5f, 0.5f));
    // PROVE_RESULT(pAmbient->Initialize())
    pMesh->Initialize();

    return static_cast<int>(errorType);
}

int Engine::Run()
{
    if (pViewport)
    {
        while (!glfwWindowShouldClose(pViewport->GetWindow()))
        {
            pViewport->Update();
            pMaterial->Update();
            // pAmbient->Update();
            pMesh->Update();

            pCamera->SetCameraData(GetDefaultCameraData());
            pCamera->Update();
            
            pViewport->Draw();
            pMaterial->Draw();
            // pAmbient->Draw();
            pMesh->Draw();

            pViewport->LateDraw();
        }
    }
    else
    {
        errorType = MessageType::RUN_VIEWPORT_FAILED;
        ErrorHandler::LogError("Cannot run application. Viewport is null.", errorType, __FILE__, __LINE__);
        return static_cast<int>(errorType);
    }

    return static_cast<int>(errorType);
}

void Engine::Finalize()
{
}