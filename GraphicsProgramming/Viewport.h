#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <string>

#include "ErrorHandler.h"
#include "Material.h"
#include "IObject.h"
#include "Camera.h"
#include "Color.h"

// Deleter for the unique pointer to the GLFW window
struct GLFWwindowDeleter
{
    void operator()(GLFWwindow* ptr) const
    {
        glfwDestroyWindow(ptr);
    }
};

class Viewport final : public IObject
{
public:
    Viewport(const int majorVersion, const int minorVersion, const int width, const int height, const int offsetX, const int offsetY, std::string title, Color color)
    : glfwMajorVersion(majorVersion), glfwMinorVersion(minorVersion), windowWidth(width), windowHeight(height), windowOffsetX(offsetX),
        windowOffsetY(offsetY), windowTitle(std::move(title)), windowColor(color)
    {
        // Config 
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwMinorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Window Creation. Unique pointer to the GLFW window
        pWindow = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>(glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr));
    }

    GLFWwindow* GetWindow() const { return pWindow.get(); }
    
    int Initialize() override;
    int Draw() override;
    int Update();
    int LateDraw();
    void Finalize() const override;

    void SetMaterial(Material* material) { this->pMaterial = material; }
    void SetCamera(Camera* camera) { this->pCamera = camera; }

private:
    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> pWindow;
    Material* pMaterial;
    Camera* pCamera;
    
    MessageType message = MessageType::SUCCESS;
    
    // GLFW values (versions)

    int glfwMajorVersion;
    int glfwMinorVersion;

    // Window

    int windowWidth;
    int windowHeight;
    int windowOffsetX;
    int windowOffsetY;
    std::string windowTitle;
    
    Color windowColor;

    // Input
    
    float rotationSpeed = 0.25f;
    float mouseSensitivity = 0.1f;

    // Camera

    bool firstMouse;
    glm::vec3 cameraFront;
    float lastX;
    float lastY;
    float yaw;
    float pitch;
    float fov;

    // Time between current frame and last frame
    
    float deltaTime = 0.0f;	
    float lastFrame = 0.0f;

    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void MouseCallback(GLFWwindow* window, double xPos, double yPos);
    void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    void ProcessInput() const;
};

#endif // !VIEWPORT_H
