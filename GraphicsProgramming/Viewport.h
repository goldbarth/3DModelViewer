#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <string>

#include "ErrorHandler.h"
#include "IObject.h"
#include "Color.h"

// Global variables (for now)

inline std::function<void()> forwardInput = nullptr;
inline std::function<void()> backwardInput = nullptr;
inline std::function<void()> leftInput = nullptr;
inline std::function<void()> rightInput = nullptr;

class Viewport : public IObject
{
public:
    Viewport(const int majorVersion, const int minorVersion, const int width, const int height, const int offsetX, const int offsetY, std::string title, const Color color) :
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
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void ProcessInput() const;

public:
    GLFWwindow* GetWindow() const { return pWindow; }

    void SetForwardInput(std::function<void()> input) { forwardInput = std::move(input); }
    void SetBackwardInput(std::function<void()> input) { backwardInput = std::move(input); }
    void SetLeftInput(std::function<void()> input) { leftInput = std::move(input); }
    void SetRightInput(std::function<void()> input) { rightInput = std::move(input); }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;
    int LateDraw();

private:
    
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

    // -----------
    
    GLFWwindow* pWindow = nullptr;
    
    ErrorType errorType = ErrorType::SUCCESS;
};

#endif // !VIEWPORT_H
