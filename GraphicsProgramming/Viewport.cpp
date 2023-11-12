#include "ErrorHandler.h"
#include "Viewport.h"
#include "Color.h"

// Callback

// Set the framebuffer size callback using a lambda, because it is a static function and cannot access member variables.
// It needs to be static because it is one way to set the offset from the viewport @ the constructor initialization.
auto Viewport::FramebufferSizeCallback(GLFWwindow* window, const int width, int height) -> void
{
    // Access member variables using the captured lambda
    const auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
    glViewport(viewport->windowOffsetX, viewport->windowOffsetY, width, height);
}

// Helper function

/// <summary>Handles the window closing.</summary>
void Viewport::ProcessInput() const
{
    if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, true);
}

// Viewport functions

int Viewport::Initialize()
{
    // Initialize GLFW
    if (pWindow == nullptr)
    {
        glfwTerminate();
        errorType = ErrorType::GLFW_WINDOW_INIT_FAILED;
        ErrorHandler::LogError(errorType);
        return static_cast<int>(errorType);
    }

    glfwMakeContextCurrent(pWindow);

    glfwSetWindowUserPointer(pWindow, this);
    glfwSetFramebufferSizeCallback(pWindow, [](GLFWwindow* window, const int width, const int height)
    {
        const auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        viewport->FramebufferSizeCallback(window, width, height);
    });

    // GLAD: Load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        errorType = ErrorType::GLAD_INIT_FAILED;
        ErrorHandler::LogError(errorType);
        return static_cast<int>(errorType);
    }

    return static_cast<int>(errorType);
}

void Viewport::Finalize()
{
    glfwTerminate();
}

int Viewport::Update()
{
    ProcessInput();
    
    return static_cast<int>(errorType);
}

int Viewport::LateDraw()
{
    glfwSwapBuffers(pWindow);
    glfwPollEvents();
    
    return static_cast<int>(errorType);
}

int Viewport::Draw()
{
    glClearColor(windowColor.red, windowColor.green, windowColor.blue, windowColor.alpha);
    glClear(GL_COLOR_BUFFER_BIT);

    LateDraw();
    
    return static_cast<int>(errorType);
}





