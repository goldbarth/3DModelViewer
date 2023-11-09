#ifndef ENGINE_H
#define ENGINE_H

#include "Viewport.h"

class Engine
{
public:
    int Initialize();
    int Run();
    void Finalize();

private:
    Viewport* pViewport = nullptr;
    ErrorType errorType = ErrorType::SUCCESS;
    
    // GLFW values (versions)

    const int GLFW_MAJOR_VERSION = 3;
    const int GLFW_MINOR_VERSION = 3;

    // Window values

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 360;
    const int WINDOW_OFFSET_X = 0;
    const int WINDOW_OFFSET_Y = 0;

    const std::string WINDOW_TITLE = "Glodbarth Engine 1.0";

    // Colors

    const Color BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
    const Color TURQUOISE = Color(0.0f, 0.5f, 0.5f, 1.0f);
    const Color DARK_GRAY = Color(0.25f, 0.25f, 0.25f, 1.0f);
    const Color LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f, 1.0f);

};

#endif // !ENGINE_H