#ifndef SHADER_H
#define SHADER_H

#include <glm/fwd.hpp>
#include <sstream>
#include <string>

class Shader
{
public:
    unsigned int ID;
    
    void Compile(std::pair<const char*, const char*> shaderSources);
    void Compile(const char* vShaderSource, const char* fShaderSource);
    void CreateShader(const char* shaderSource, unsigned& shader, const char* str);
    void UseProgram() const;
    
    // Utility uniform functions
    
    void SetBool(const std::string &name, bool value) const;  
    void SetInt(const std::string &name, int value) const;   
    void SetFloat(const std::string &name, float value) const;
    void SetVec2(const std::string &name, const glm::vec2 &value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string &name, const glm::vec3 &value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetMat4(const std::string &name, const glm::mat4 &material) const;

private:
    static void CheckCompileErrors(unsigned int shader, const std::string& type);
};

#endif // !SHADER_H
