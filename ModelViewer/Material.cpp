#include <glad/glad.h>

#include "Material.h"

void Material::AddUniformVector3(const std::string& name, const Color& color) const
{
    const GLfloat r = color.r, g = color.g, b = color.b;
    
    const GLuint lightColorLocation = glGetUniformLocation(*GetShaderProgram(), name.c_str());
    glUniform3f(static_cast<GLint>(lightColorLocation), r, g, b);
}

int Material::Initialize()
{
    // Build and compile vertex shader
    
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* vertexShaderSource = pVertexShaderSource.get();
    glShaderSource(vertexShader, SOURCE_COUNT, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    constexpr int bufferSize = 512;
    char infoLog[bufferSize];
    int success = 0;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, bufferSize, nullptr, infoLog);
        errorType = MessageType::VERTEX_SHADER_COMPILATION_FAILED;
        ErrorHandler::LogError(errorType, __FILE__, __LINE__);
        ErrorHandler::LogError(infoLog,  __FILE__, __LINE__);
        
        return static_cast<int>(errorType);
    }

    // Build and compile fragment shader
    
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* fragmentShaderSource = pFragmentShaderSource.get();
    glShaderSource(fragmentShader, SOURCE_COUNT, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, bufferSize, nullptr, infoLog);
        errorType = MessageType::FRAGMENT_SHADER_COMPILATION_FAILED;
        ErrorHandler::LogError(errorType, __FILE__, __LINE__);
        ErrorHandler::LogError(infoLog,  __FILE__, __LINE__);
    
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
        errorType = MessageType::SHADER_PROGRAM_LINK_FAILED;
        ErrorHandler::LogError(errorType, infoLog,__FILE__, __LINE__);
        
        return static_cast<int>(errorType);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return static_cast<int>(errorType);
}

int Material::Update()
{
    return static_cast<int>(MessageType::SUCCESS);
}

int Material::Draw()
{
    glUseProgram(*pShaderProgram);
    return static_cast<int>(MessageType::SUCCESS);
}

void Material::Finalize()
{
    glDeleteProgram(*pShaderProgram);
}
