#include <glad/glad.h>

#include "Material.h"


const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";



int Material::Initialize()
{
    // Build and compile vertex shader
    
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success = 0;
    char infoLog[512];
    constexpr int bufferSize = 512;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, bufferSize, nullptr, infoLog);
        errorType = ErrorType::VERTEX_SHADER_COMPILATION_FAILED;
        ErrorHandler::LogError(errorType);
        
        return static_cast<int>(errorType);
    }

    // Build and compile fragment shader
    
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, bufferSize, nullptr, infoLog);
        errorType = ErrorType::FRAGMENT_SHADER_COMPILATION_FAILED;
        ErrorHandler::LogError(errorType);
        
        return static_cast<int>(errorType);
    }

    // Link shaders

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, bufferSize, nullptr, infoLog);
        errorType = ErrorType::SHADER_PROGRAM_LINK_FAILED;
        ErrorHandler::LogError(errorType);
        
        return static_cast<int>(errorType);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return static_cast<int>(errorType);
}

int Material::Update()
{
    return static_cast<int>(ErrorType::SUCCESS);
}

int Material::Draw()
{
    glUseProgram(shaderProgram);
    return static_cast<int>(ErrorType::SUCCESS);
}

void Material::Finalize()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}
