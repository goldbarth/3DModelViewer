#include "ErrorHandler.h"
#include "Viewport.h"
#include "Color.h"

int Viewport::Initialize()
{
    if (!pWindow)
    {
        glfwTerminate();
        message = MessageType::GLFW_WINDOW_INIT_FAILED;
        ErrorHandler::LogError(message, __FILE__, __LINE__);
        
        return static_cast<int>(message);
    }

    // Set the viewport
    glfwMakeContextCurrent(pWindow.get());
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
        
        return static_cast<int>(message);
    }

    // TODO: Depth buffer setup
    //glEnable(GL_DEPTH_TEST);

    return static_cast<int>(message);
}

void Viewport::Finalize()
{
    glfwTerminate();
}

int Viewport::Update()
{
    ProcessInput();
    
    return static_cast<int>(message);
}

int Viewport::LateDraw()
{
    glfwSwapBuffers(pWindow.get());
    glfwPollEvents();
    
    return static_cast<int>(message);
}

int Viewport::Draw()
{
    glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);
    // TODO: Depth buffer clear
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glClear(GL_COLOR_BUFFER_BIT);

    LateDraw();
    
    return static_cast<int>(message);
}

// Input system

/// <summary>Handles the user input.</summary>
void Viewport::ProcessInput() const
{
    if (glfwGetKey(pWindow.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow.get(), true);

    // Camera movement
    if (glfwGetKey(pWindow.get(), GLFW_KEY_W) == GLFW_PRESS)
        if (forwardInput != nullptr) forwardInput();
    if (glfwGetKey(pWindow.get(), GLFW_KEY_S) == GLFW_PRESS)
        if (backwardInput != nullptr) backwardInput();
    if (glfwGetKey(pWindow.get(), GLFW_KEY_A) == GLFW_PRESS)
        if (leftInput != nullptr) leftInput();
    if (glfwGetKey(pWindow.get(), GLFW_KEY_D) == GLFW_PRESS)
        if (rightInput != nullptr) rightInput();
}

// Callback

auto Viewport::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height) -> void
{
    // Access member variables (windowOffsetX, windowOffsetY) using the captured lambda expression
    const auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
    glViewport(viewport->windowOffsetX, viewport->windowOffsetY, width, height);
}



