#include <glad/glad.h>

#include "Material.h"

int Material::Initialize()
{
    // Build and compile vertex shader
    
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &pVertexShaderSource, nullptr);
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
    
    glShaderSource(fragmentShader, 1, &pFragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, bufferSize, nullptr, infoLog);
        errorType = ErrorType::FRAGMENT_SHADER_COMPILATION_FAILED;
        ErrorHandler::LogError(errorType);
        
        return static_cast<int>(errorType);
    }

    // Link shaders

    *pShaderProgram = glCreateProgram();
    glAttachShader(*pShaderProgram, vertexShader);
    glAttachShader(*pShaderProgram, fragmentShader);
    glLinkProgram(*pShaderProgram);
    glGetProgramiv(*pShaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(*pShaderProgram, bufferSize, nullptr, infoLog);
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
    glUseProgram(*pShaderProgram);
    return static_cast<int>(ErrorType::SUCCESS);
}

void Material::Finalize()
{
    glDeleteProgram(*pShaderProgram);
}
