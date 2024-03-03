#ifndef MATERIAL_H
#define MATERIAL_H

#include "ErrorHandler.h"
#include "FileSystem.h"
#include "IObject.h"
#include "Model.h"
#include "Shader.h"

class Material final : public IObject
{
public:
    Material() : pShader(std::make_unique<Shader>()), shaderProgram(0)
    {} 
    
    int Initialize() override;
    int Draw() override;
    void Finalize() const override;
    
    Shader* GetShader() const { return pShader.get(); }

private:
    std::unique_ptr<Shader> pShader;
    std::unique_ptr<Model> pModelOne;
    
    unsigned int shaderProgram;
    FileSystem file;

    std::string vertexShaderFileName = "ModelVertexShader.glsl";
    std::string fragmentShaderFileName = "ModelFragmentShader.glsl";
    
    MessageType message = MessageType::SUCCESS;
};

#endif // !MATERIAL_H
