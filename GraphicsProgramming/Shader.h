#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <string>
#include <sstream>
#include <glm/fwd.hpp>

class Shader
{
public:
    unsigned int ID;

    void Compile(const char* vShaderSource, const char* fShaderSource);
    
    void UseProgram() const;
    
    // utility uniform functions
    void SetBool(const std::string &name, bool value) const;  
    void SetInt(const std::string &name, int value) const;   
    void SetFloat(const std::string &name, float value) const;
    void SetMat4(const std::string &name, const glm::mat4 &material) const;

private:
    static void CheckCompileErrors(unsigned int shader, const std::string& type);
};

#endif // !DATA_HANDLER_H
