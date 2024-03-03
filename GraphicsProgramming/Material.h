﻿#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>

#include "ErrorHandler.h"
#include "FileSystem.h"
#include "IObject.h"
#include "Shader.h"

class Material final : public IObject
{
public:
    Material() : pShader(std::make_unique<Shader>()), shaderProgram(0)
    {} 
private:
    const GLsizei SOURCE_COUNT = 1;
    std::string vertexShaderFileName = "VertexShader.glsl";
    std::string fragmentShaderFileName = "FragmentShader.glsl";

public:
    int Initialize() override;
    int Update() override;
    int Draw() override;
    void Finalize() const;

void SetUniformMat4(const std::string& name, const glm::mat4& value) const;

private:
    std::unique_ptr<Shader> pShader;
    
    unsigned int shaderProgram;
    FileSystem file;
    
    MessageType message = MessageType::SUCCESS;
};

#endif // !MATERIAL_H
