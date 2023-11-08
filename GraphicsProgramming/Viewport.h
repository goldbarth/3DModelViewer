#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "IObject.h"
#include "Color.h"

class Viewport : public IObject
{
public:
    Viewport(int majorVersion, int minorVersion, int width, int height, std::string title, Color color) :
        glfwMajorVersion(majorVersion), glfwMinorVersion(minorVersion),
        windowWidth(width), windowHeight(height), windowTitle(title), windowColor(color)
    {
        // Config
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwMinorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Window
        pWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
    }
    
    [[nodiscard]] GLFWwindow* getWindow() const { return pWindow; }
    
    // IObject functions
    
    int initialize() override;
    void finalize() override;
    int update() override;
    int draw() override;

private:

    GLFWwindow* pWindow = nullptr;
    
    // GLFW values (versions)

    int glfwMajorVersion;
    int glfwMinorVersion = 3;

    // Window values

    int windowWidth;
    int windowHeight;
    std::string windowTitle;

    // Color
    
    Color windowColor;
    
    // Helper functions

    static void printLogError(const std::string& message);
    void processInput() const;
};

#endif // !VIEWPORT_H
