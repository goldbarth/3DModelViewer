#ifndef ENGINE_H
#define ENGINE_H

#include "FileDataHandler.h"
#include "Viewport.h"
#include "Material.h"
#include "Mesh.h"

class Engine
{
public:
    explicit Engine(DataManager* pData) : pData(pData) {  }
    
    int Initialize();
    int Run();
    void Finalize();

private:
    DataManager* pData = nullptr;
    Viewport* pViewport = nullptr;
    Material* pMaterial = nullptr;
    Mesh* pMesh = nullptr;
    
    ErrorType errorType = ErrorType::SUCCESS;
    
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
    static const Color BLACK;
    static const Color TURQUOISE; 
    static const Color DARK_GRAY;
    static const Color LIGHT_GRAY;

    const char* pVertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\n\0";

    const char* pFragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    float* pVertices = new float[18]
    {
        -0.9f, -0.5f, 0.0f, // left
        0.0f, -0.5f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, // top

        // 2. Triangle
        0.0f, -0.5f, 0.0f, // left
        0.9f, -0.5f, 0.0f, // right
        0.45f, 0.5f, 0.0f, // top
    };
};

#endif // !ENGINE_H