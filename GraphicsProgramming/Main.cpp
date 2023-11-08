#include "Viewport.h"
#include "Color.h"

// Global constants

// GLFW values (versions)

const int GLFW_MAJOR_VERSION = 3;
const int GLFW_MINOR_VERSION = 3;

// Window values

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 360;
const std::string WINDOW_TITLE = "Glodbarth Engine 1.0";

// Colors

const Color BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color DARK_GRAY = Color(0.25f, 0.25f, 0.25f, 1.0f);
const Color LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f, 1.0f);
const Color TURQUOISE = Color(0.0f, 0.5f, 0.5f, 1.0f);

Viewport* viewport = nullptr;

void RunApplication(Viewport* viewport)
{
    if (viewport != nullptr)
    {
        viewport->initialize();
        while (!glfwWindowShouldClose(viewport->getWindow()))
        {
            viewport->update();
            viewport->draw();
        }
        viewport->finalize();
    }
}

int main(int argc, char* argv[])
{
    if (viewport == nullptr)
        viewport = new Viewport(GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION,
                                WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, TURQUOISE);
    RunApplication(viewport);
    
    if (viewport != nullptr)
    {
        delete viewport;
        viewport = nullptr;
    }
    
    return 0;
}
