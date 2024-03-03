#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "ErrorHandler.h"
#include "IObject.h"
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

    Viewport(const int majorVersion, const int minorVersion, const int width, const int height, const int offsetX, const int offsetY, std::string title, Color color) :
        glfwMajorVersion(majorVersion), glfwMinorVersion(minorVersion), windowWidth(width), windowHeight(height), windowOffsetX(offsetX),
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
    
    virtual ~Viewport() = default;

    GLFWwindow* GetWindow() const { return pWindow.get(); }
    
    int Initialize() override;
    int Draw() override;
    int Update();
    int LateDraw();
    void Finalize() const override;

private:

    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> pWindow;
    MessageType message = MessageType::SUCCESS;
    
    // GLFW values (versions)

    int glfwMajorVersion;
    int glfwMinorVersion;

    // Window values

    int windowWidth;
    int windowHeight;
    int windowOffsetX;
    int windowOffsetY;
    std::string windowTitle;

    // Color
    
    Color windowColor = Color(0.2f, 0.3f, 0.3f, 1.0f);
    
    // Helper functions

    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void ProcessInput() const;
};

#endif // !VIEWPORT_H
