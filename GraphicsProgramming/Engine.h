#ifndef ENGINE_H
#define ENGINE_H

#include "Material.h"
#include "Mesh.h"
#include "Viewport.h"

class Engine
{
public:
    int Initialize();
    int Run();
    void Finalize();
    
    static void CreateMesh();

private:
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

};

#endif // !ENGINE_H