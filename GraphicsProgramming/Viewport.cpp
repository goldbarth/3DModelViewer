#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "ErrorHandler.h"
#include "Viewport.h"
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
    
    SetCallbacks();

    // tell GLFW to capture our mouse
    glfwSetInputMode(pWindow.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
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
    // Calculate the time between the current frame and the last frame
    const float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    ProcessInput();
    
    return static_cast<int>(message);
}

int Viewport::Draw()
{
    // Clear the color buffer
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

void Viewport::Finalize() const
{
    glfwTerminate();
}

void Viewport::SetCallbacks()
{
    // Set the viewport object as the user pointer for the window
    glfwSetWindowUserPointer(pWindow.get(), this);
    
    glfwSetFramebufferSizeCallback(pWindow.get(), [](GLFWwindow* window, const int width, const int height)
    {
        auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        viewport->FramebufferSizeCallback(window, width, height);
    });

    glfwSetCursorPosCallback(pWindow.get(), [](GLFWwindow* window, double xPos, double yPos)
    {
        auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        viewport->MouseCallback(window, xPos, yPos);
    });
    
    glfwSetScrollCallback(pWindow.get(), [](GLFWwindow* window, double xOffset, double yOffset)
    {
        const auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        viewport->ScrollCallback(window, xOffset, yOffset);
    });
}



void Viewport::ProcessInput() const
{
    CloseWindow();
    WireframeToggle();
    ObjectRotation();
    CameraMovement();
}

void Viewport::ObjectRotation() const
{
    if (glfwGetKey(pWindow.get(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        pMaterial->AdjustObjectYaw(rotationSpeed);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_LEFT) == GLFW_PRESS)
        pMaterial->AdjustObjectYaw(-rotationSpeed);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_UP) == GLFW_PRESS)
        pMaterial->AdjustObjectPitch(rotationSpeed);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_DOWN) == GLFW_PRESS)
        pMaterial->AdjustObjectPitch(-rotationSpeed);
}

void Viewport::CameraMovement() const
{
    if (glfwGetKey(pWindow.get(), GLFW_KEY_W) == GLFW_PRESS)
        pCamera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_S) == GLFW_PRESS)
        pCamera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_A) == GLFW_PRESS)
        pCamera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_D) == GLFW_PRESS)
        pCamera->ProcessKeyboard(RIGHT, deltaTime);
}

void Viewport::WireframeToggle() const
{
    if (glfwGetKey(pWindow.get(), GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(pWindow.get(), GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Viewport::CloseWindow() const
{
    if (glfwGetKey(pWindow.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow.get(), true);
}

// Callbacks

// Set the framebuffer size callback using a lambda, because it is a static function and cannot access member variables.
// It needs to be static because it is one way to set the offset from the viewport @ the constructor initialization.
void Viewport::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    // Access member variables using the captured lambda
    const auto* viewport = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
    glViewport(viewport->windowOffsetX, viewport->windowOffsetY, width, height);
}

void Viewport::MouseCallback(GLFWwindow* window, const double xPosIn, const double yPosIn)
{
    const float xPos = static_cast<float>(xPosIn);
    const float yPos = static_cast<float>(yPosIn);

    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    
    lastX = xPos;
    lastY = yPos;
    
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    pCamera->ProcessMouseMovement(xOffset, yOffset);
}

void Viewport::ScrollCallback(GLFWwindow* window, const double xOffset, const double yOffset) const
{
    pCamera->ProcessMouseScroll(static_cast<float>(yOffset));
}





