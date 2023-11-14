#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "FileDataHandler.h"
//#include "Variables.h"
#include "Viewport.h"
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

    // Colors
    
    static const Color GOLD;
    static const Color BLACK;
    static const Color TURQUOISE; 
    static const Color DARK_GRAY;
    static const Color LIGHT_GRAY;

    // Pointers
    
    DataManager* pData = nullptr;
    Viewport* pViewport = nullptr;
    Material* pMaterial = nullptr;
    // Ambient* pAmbient = nullptr;
    Mesh* pMesh = nullptr;

    // Error handling
    
    ErrorType errorType = ErrorType::SUCCESS;
    
    // Shader values

    std::vector<Vertex> vertices = std::vector
    {
        Vertex{glm::vec3(-0.9f, -0.5f, 0.0f), Color(1.0f, 0.84f, 0.0f, 1.0f)}, // left
        Vertex{glm::vec3( 0.0f, -0.5f, 0.0f), Color(1.0f, 0.84f, 0.0f, 1.0f)}, // right
        Vertex{glm::vec3(-0.45f, 0.5f, 0.0f), Color(1.0f, 0.84f, 0.0f, 1.0f)}, // top
        
        // 2. Triangle
        Vertex{glm::vec3(0.0f, -0.5f, 0.0f), Color(1.0f, 0.84f, 0.0f, 1.0f)}, // left
        Vertex{glm::vec3(0.9f, -0.5f, 0.0f), Color(1.0f, 0.84f, 0.0f, 1.0f)}, // right
        Vertex{glm::vec3(0.45f, 0.5f, 0.0f), Color(1.0f, 0.84f, 0.0f, 1.0f)} // top
    };

    std::vector<unsigned int> indices = std::vector<unsigned int>
    {
        0, 1, 2, // first triangle face
        2, 1, 3 // second triangle face
    };
};

#endif // !ENGINE_H