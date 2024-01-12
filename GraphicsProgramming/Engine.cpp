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
        pMaterial = std::make_unique<Material>(pData, pData->GetShaderFolderPath(), pDefaultVertexShaderName, pDefaultFragmentShaderName);
        //pAmbient = std::make_unique<Ambient>(pData, pData->GetShaderFolderPath(), pAmbientVertexShaderName, pAmbientFragmentShaderName);
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
        errorType = ErrorType::ENGINE_INIT_FAILED;
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
    if (pViewport != nullptr)
    {
        while (!glfwWindowShouldClose(pViewport->GetWindow()))
        {
            PROVE_RESULT(pViewport->Update())
            PROVE_RESULT(pMaterial->Update())
            // PROVE_RESULT(pAmbient->Update())
            PROVE_RESULT(pMesh->Update())

            pCamera->SetCameraData(CameraData{ DEFAULT_CAMERA_FOV, DEFAULT_CAMERA_NEAR,
                DEFAULT_CAMERA_FAR, pMaterial->GetShaderProgram(),
                CAMERA_UNIFORM_NAME.c_str()
            });
            PROVE_RESULT(pCamera->Update())

            PROVE_RESULT(pViewport->Draw())
            PROVE_RESULT(pMaterial->Draw())
            // PROVE_RESULT(pAmbient->Draw())
            PROVE_RESULT(pMesh->Draw())
            
            PROVE_RESULT(pViewport->LateDraw())
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
}
