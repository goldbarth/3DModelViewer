#include "ErrorHandler.h"
#include "Viewport.h"
#include "Color.h"

// Viewport functions

int Viewport::Initialize()
{
    // Initialize GLFW
    if (pWindow == nullptr)
    {
        glfwTerminate();
        errorType = ErrorType::GLFW_WINDOW_INIT_FAILED;
        ErrorHandler::LogError(errorType, __FILE__, __LINE__);
        
        return static_cast<int>(errorType);
    }

    glfwMakeContextCurrent(pWindow);

    glfwSetWindowUserPointer(pWindow, this);
    glfwSetFramebufferSizeCallback(pWindow, [](GLFWwindow* window, const int width, const int height)
    {
        auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        viewport->FramebufferSizeCallback(window, width, height);
    });

    // GLAD: Load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        errorType = ErrorType::GLAD_INIT_FAILED;
        ErrorHandler::LogError(errorType, __FILE__, __LINE__);
        
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

// Input system

/// <summary>Handles the user input.</summary>
void Viewport::ProcessInput() const
{
    if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, true);

    // Camera movement
    if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
        if (forwardInput != nullptr) forwardInput();
    if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
        if (backwardInput != nullptr) backwardInput();
    if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
        if (leftInput != nullptr) leftInput();
    if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
        if (rightInput != nullptr) rightInput();
}

// Callback

auto Viewport::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height) -> void
{
    // Access member variables (windowOffsetX, windowOffsetY) using the captured lambda expression
    const auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
    glViewport(viewport->windowOffsetX, viewport->windowOffsetY, width, height);
}



