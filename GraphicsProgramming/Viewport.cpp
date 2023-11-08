#include <iostream>

#include "Viewport.h"
#include "Color.h"

// Global constants

const int OFFSET_X = 0;
const int OFFSET_Y = 0;

// Callback

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(OFFSET_X, OFFSET_Y, width, height);
}

// Helper functions

/// <summary>Prints an red error message to the console.</summary>
void Viewport::printLogError(const std::string& message)
{
    fprintf(stderr, "\x1b[31mError: %s\x1b[0m\n", message.c_str());
}

/// <summary>Handles the window closing.</summary>
void Viewport::processInput() const
{
    if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // Close window
        glfwSetWindowShouldClose(pWindow, true);
    }
}

int Viewport::initialize()
{
    // Initialize GLFW
    if (pWindow == nullptr)
    {
        printLogError("GLFW initialization failed");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pWindow);
    glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);

    // GLAD: Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printLogError("Failed to initialize GLAD");
        return -2;
    }

    return 0;
}

void Viewport::finalize()
{
    glfwTerminate();
}

int Viewport::update()
{
    processInput();
    return 0;
}

int Viewport::draw()
{

    glClearColor(windowColor.red, windowColor.green, windowColor.blue, windowColor.alpha);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
    return 0;
}





