#include "ErrorHandler.h"
#include "Viewport.h"

#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Color.h"


int Viewport::Initialize()
{
    if (!pWindow)
    {
        message = MessageType::GLFW_WINDOW_INIT_FAILED;
        ErrorHandler::LogError(message, __FILE__, __LINE__);
        glfwTerminate();
        
        return static_cast<int>(message);
    }

    // This is necessary for any OpenGL calls to work.
    glfwMakeContextCurrent(pWindow.get());

    // Set the viewport size and position
    glfwSetWindowUserPointer(pWindow.get(), this);
    glfwSetFramebufferSizeCallback(pWindow.get(), [](GLFWwindow* window, const int width, const int height)
    {
        auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        viewport->FramebufferSizeCallback(window, width, height);
    });
    
    // GLAD: Load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        message = MessageType::GLAD_INIT_FAILED;
        ErrorHandler::LogError(message, __FILE__, __LINE__);
        Finalize();
        
        return static_cast<int>(message);
    }

    return static_cast<int>(message);
}

int Viewport::Update()
{
    ProcessInput();
    
    return static_cast<int>(message);
}

int Viewport::Draw()
{
    // Render here (clear the screen)
    glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    return static_cast<int>(message);
}

int Viewport::LateDraw()
{
    // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(pWindow.get());
    // Check for IO events
    glfwPollEvents();
    
    return static_cast<int>(message);
}

void Viewport::Finalize()
{
    glfwTerminate();
}

void Viewport::ProcessInput() const
{
    if (glfwGetKey(pWindow.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow.get(), true);
    }

    // Wireframe mode
    if (glfwGetKey(pWindow.get(), GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Callback

// Set the framebuffer size callback using a lambda, because it is a static function and cannot access member variables.
// It needs to be static because it is one way to set the offset from the viewport @ the constructor initialization.
void Viewport::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    // Access member variables using the captured lambda
    const auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
    glViewport(viewport->windowOffsetX, viewport->windowOffsetY, width, height);
}





