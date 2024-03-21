#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>

#include "ErrorHandler.h"
#include "Shader.h"

unsigned Shader::CreateShader(const char* shaderSource, const int shaderType, const ErrorTypes& type)
{
    const unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    CheckCompileErrors(shader, type);
    
    return shader;
}


void Shader::CreateShaderProgram(const unsigned int vertex, const unsigned int fragment)
{
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, PROGRAM);
}

void Shader::Compile(const std::pair<const char*, const char*> shaderSources)
{
    const unsigned int vertex = CreateShader(shaderSources.first, GL_VERTEX_SHADER, VERTEX);
    const unsigned int fragment = CreateShader(shaderSources.second, GL_FRAGMENT_SHADER, FRAGMENT);
    CreateShaderProgram(vertex, fragment);
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::UseProgram() const
{
    glUseProgram(ID); 
}

void Shader::SetBool(const std::string& name, const bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value)); 
}

void Shader::SetInt(const std::string& name, const int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::SetFloat(const std::string& name, const float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::SetVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void Shader::SetVec3(const std::string& name, const float x, const float y, const float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& material) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &material[0][0]);
}

void Shader::CheckCompileErrors(const unsigned int shader, const ErrorTypes& type)
{
    constexpr int bufferSize = 1024;
    
    int success;
    char infoLog[bufferSize];
    if (type != PROGRAM)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, bufferSize, nullptr, infoLog);
            ErrorHandler::LogError(MessageType::SHADER_COMPILATION_FAILED, "Error of type: " + std::to_string(type) + "\n" + infoLog + "\n -- --------------------------------------------------- -- ", __FILE__, __LINE__);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, bufferSize, nullptr, infoLog);
            ErrorHandler::LogError(MessageType::SHADER_PROGRAM_LINK_FAILED, "Error of type: " + std::to_string(type) + "\n" + infoLog + "\n -- --------------------------------------------------- -- ", __FILE__, __LINE__);
        }
    }
}
    
