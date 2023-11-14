#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "ErrorHandler.h"
#include "IObject.h"
#include "Color.h"

class Viewport : public IObject
{
public:
    Viewport(int majorVersion, int minorVersion, int width, int height, int offsetX, int offsetY, std::string title, Color color) :
        glfwMajorVersion(majorVersion), glfwMinorVersion(minorVersion), windowWidth(width), windowHeight(height), windowOffsetX(offsetX),
        windowOffsetY(offsetY), windowTitle(std::move(title)), windowColor(color)
    {
        // Config
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwMinorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Window
        pWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
    }
private:
    // Helper functions

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void ProcessInput() const;

public:
    [[nodiscard]] GLFWwindow* GetWindow() const { return pWindow; }
    
    // IObject functions
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;
    int LateDraw();

private:

    GLFWwindow* pWindow = nullptr;
    ErrorType errorType = ErrorType::SUCCESS;
    
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
    
    Color windowColor;
};

#endif // !VIEWPORT_H
