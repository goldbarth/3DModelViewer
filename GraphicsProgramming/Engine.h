﻿#ifndef ENGINE_H
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
    
    int Initialize();
    int Run();
    void Finalize();

private:
    // GLFW values (versions)

    static const int GLFW_MAJOR_VERSION;
    static const int GLFW_MINOR_VERSION;

    // Window values

    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const int WINDOW_OFFSET_X;
    static const int WINDOW_OFFSET_Y;

    static const std::string WINDOW_TITLE;

    // Camera values
    
    static const glm::vec3 CAMERA_POSITION;
    static const glm::vec3 CAMERA_ORIENTATION;
    static const glm::vec3 CAMERA_UP;
    
    static const std::string CAMERA_UNIFORM_NAME;

    static const float DEFAULT_CAMERA_FOV;
    static const float DEFAULT_CAMERA_NEAR;
    static const float DEFAULT_CAMERA_FAR;

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