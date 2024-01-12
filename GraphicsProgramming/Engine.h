#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "FileDataHandler.h"
#include "Viewport.h"
#include "Camera.h"
#include "Material.h"
#include "Ambient.h"
#include "Mesh.h"
#include "TexCoords.h"
#include "VertPos.h"

class Engine
{
public:
    explicit Engine(FileDataHandler* pData) : pData(pData) {  }

    const CameraData& GetDefaultCameraData() const;
    bool InitializeObjects();
    int Initialize();
    int Run();
    void Finalize();

private:
    // GLFW values (versions)

    const int GLFW_MAJOR_VERSION = 3;
    const int GLFW_MINOR_VERSION = 3;

    // Window values

    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;
    const int WINDOW_OFFSET_X = 0;
    const int WINDOW_OFFSET_Y = 0;

    static const std::string WINDOW_TITLE;

    // Camera values
    
    static const glm::vec3 CAMERA_POSITION;
    static const glm::vec3 CAMERA_ORIENTATION;
    static const glm::vec3 CAMERA_UP;
    
    std::string CAMERA_UNIFORM_NAME = "cameraMatrix";

    const float DEFAULT_CAMERA_FOV_DEGREE = 0.45f;
    const float DEFAULT_CAMERA_NEAR = 0.1f;
    const float DEFAULT_CAMERA_FAR = 1000.0f;

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
    
    FileDataHandler* pData = nullptr;
    // Camera* pCamera = nullptr;
    // Viewport* pViewport = nullptr;
    // Material* pMaterial = nullptr;
    // Ambient* pAmbient = nullptr;
    // Mesh* pMesh = nullptr;
    
    std::unique_ptr<Camera> pCamera;
    std::unique_ptr<Viewport> pViewport;
    std::unique_ptr<Material> pMaterial;
    std::unique_ptr<Ambient> pAmbient;
    std::unique_ptr<Mesh> pMesh;

    // Error handling
    
    ErrorType errorType = ErrorType::SUCCESS;
    
    // Shader values

    static const char* pAmbientVertexShaderName;
    static const char* pAmbientFragmentShaderName;
    static const char* pDefaultVertexShaderName;
    static const char* pDefaultFragmentShaderName;
    
    Color white = Color(1.0f, 1.0f, 1.0f, 1.0f);
    Color red = Color(1.0f, 0.0f, 0.0f, 1.0f);
    Color green = Color(0.0f, 1.0f, 0.0f, 1.0f);
    Color blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
    
    std::vector<Vertex> vertices = std::vector
    {
        Vertex{VertPos(-0.5f, -0.5f, 0.0f), TexCoords(0.0f, 0.0f), Color(white)}, // left-bottom
        Vertex{VertPos( 0.5f, -0.5f, 0.0f), TexCoords(1.0f, 0.0f), Color(red)}, // right-bottom
        Vertex{VertPos(-0.5f, 0.5f, 0.0f), TexCoords(0.0f, 0.1f),Color(green)}, // top-left
        Vertex{VertPos(0.5f, 0.5f, 0.0f), TexCoords(1.0f, 1.0f),Color(blue)}, // top-right
    };

    std::vector<unsigned int> indices = std::vector<unsigned int>
    {
        0, 1, 2, // first face
        2, 1, 3 // second face
    };

    // Textures

    //TODO: Make this a parameter later
    unsigned int textureID = 0;
    std::string textureName = "default_64x64_f1.jpg";
    std::string texturePath = std::string(pData->GetTextureFolderPath()) + textureName;

    std::vector<Texture> textures = std::vector
    {
        Texture{textureID, texturePath},
    };
};

#endif // !ENGINE_H