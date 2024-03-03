#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>

#include "ErrorHandler.h"
#include "FileSystem.h"
#include "IObject.h"
#include "Shader.h"

class Material final : public IObject
{
public:
    Material() : shaderProgram(0), pShader(std::make_unique<Shader>())
    {
    } 
private:
    const GLsizei SOURCE_COUNT = 1;

public:
    int Initialize() override;
    int Update() override;
    int Draw() override;
    void Finalize();

void SetUniformMat4(const std::string& name, const glm::mat4& value) const;

private:
    unsigned int shaderProgram;

    std::unique_ptr<Shader> pShader;

    FileSystem file;
    
    MessageType message = MessageType::SUCCESS;
};

#endif // !MATERIAL_H
