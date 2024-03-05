#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>

#include "ErrorHandler.h"
#include "Shader.h"

void Shader::CreateShader(const char* shaderSource, unsigned& shader, const char* str)
{
    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    CheckCompileErrors(shader, str);
}

void Shader::Compile(const std::pair<const char*, const char*> shaderSources)
{
    // Create and compile the shader
    unsigned int vertex;
    unsigned int fragment;
    CreateShader(shaderSources.first, vertex, "VERTEX");
    CreateShader(shaderSources.second, fragment, "FRAGMENT");
    
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

void Shader::Compile(const char* vShaderSource, const char* fShaderSource)
{
    // Create and compile the shader
    unsigned int vertex;
    unsigned int fragment;
    CreateShader(vShaderSource, vertex, "VERTEX");
    CreateShader(fShaderSource, fragment, "FRAGMENT");
    
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
    
