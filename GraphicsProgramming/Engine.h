#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "FileDataHandler.h"
#include "Viewport.h"
#include "Camera.h"
#include "Material.h"
#include "Ambient.h"
#include "Mesh.h"

class Engine
{
public:
    explicit Engine(DataManager* pData) : pData(pData) {  }
    
    int Initialize();
    int Run();
    void Finalize();

private:
    // GLFW values (versions)

    const int GLFW_MAJOR_VERSION = 3;
    const int GLFW_MINOR_VERSION = 3;

    // Window values

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 360;
    const int WINDOW_OFFSET_X = 0;
    const int WINDOW_OFFSET_Y = 0;

    static const std::string WINDOW_TITLE;

    // Camera values
    
    static const glm::vec3 CAMERA_POSITION;
    static const glm::vec3 CAMERA_ORIENTATION;
    static const glm::vec3 CAMERA_UP;
    
    const char* CAMERA_UNIFORM_NAME = "cameraMatrix";

    const float DEFAULT_CAMERA_FOV = 0.45f;
    const float DEFAULT_CAMERA_NEAR = 0.1f;
    const float DEFAULT_CAMERA_FAR = 100.0f;

    // Input values

    static const glm::vec3 FORWARD_INPUT;
    static const glm::vec3 BACKWARD_INPUT;
    static const glm::vec3 LEFT_INPUT;
    static const glm::vec3 RIGHT_INPUT;

    // Colors
    
    static const Color GOLD;
    static const Color BLACK;
    static const Color TURQUOISE; 
    static const Color DARK_GRAY;
    static const Color LIGHT_GRAY;

    // Pointers
    
    DataManager* pData = nullptr;
    Camera* pCamera = nullptr;
    Viewport* pViewport = nullptr;
    Material* pMaterial = nullptr;
    // Ambient* pAmbient = nullptr;
    Mesh* pMesh = nullptr;

    // Error handling
    
    ErrorType errorType = ErrorType::SUCCESS;
    
    // Shader values

    static const char* pAmbientVertexShaderName;
    static const char* pAmbientFragmentShaderName;
    static const char* pDefaultVertexShaderName;
    static const char* pDefaultFragmentShaderName;

    std::vector<Vertex> vertices = std::vector
    {
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), Color(1.0f, 1.0f, 1.0f, 1.0f)}, // left-bottom
        Vertex{glm::vec3( 0.5f, -0.5f, 0.0f), Color(1.0f, 0.0f, 0.0f, 1.0f)}, // right-bottom
        Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), Color(0.0f, 1.0f, 0.0f, 1.0f)}, // top-left
        Vertex{glm::vec3(0.5f, 0.5f, 0.0f), Color(0.0f, 0.0f, 1.0f, 1.0f)}, // top-right
    };

    std::vector<unsigned int> indices = std::vector<unsigned int>
    {
        0, 1, 2, // first face
        2, 1, 3 // second face
    };
};

#endif // !ENGINE_H