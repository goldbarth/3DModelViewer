#include "Shader.h"

#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>

#include "ErrorHandler.h"

void Shader::Compile(const char* vShaderSource, const char* fShaderSource)
{
    // Create the vertex shader
    const unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSource, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    
    // Create the fragment shader
    const unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSource, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    
    // Create the shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");
    
    // Delete the shaders as they're linked into our program now and no longer necessary
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

void Shader::SetMat4(const std::string& name, const glm::mat4& material) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &material[0][0]);
}

void Shader::CheckCompileErrors(const unsigned shader, const std::string& type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            ErrorHandler::LogError(MessageType::SHADER_COMPILATION_FAILED, "Error of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ", __FILE__, __LINE__);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            ErrorHandler::LogError(MessageType::SHADER_PROGRAM_LINK_FAILED, "Error of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ", __FILE__, __LINE__);
        }
    }
}
    
