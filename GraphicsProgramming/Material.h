#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "ErrorHandler.h"
#include "DataHandler.h"
#include "IObject.h"
#include "Shader.h"
#include "Camera.h"

class Material final : public IObject
{
public:
    Material() : pModelShader(std::make_unique<Shader>())
    {} 
    
    int Initialize() override;
    int Draw() override;
    void Finalize() const override;
    int Update(const Camera* camera);
    
    Shader* GetModelShader() const { return pModelShader.get(); }

    float GetObjectAngle() const { return yAngle; }
    void SetObjectYaw(const float aAngle) { this->yAngle = aAngle; }
    float GetObjectPitch() const { return xAngle; }
    void SetObjectPitch(const float aAngle) { this->xAngle = aAngle; }


private:
    std::unique_ptr<Shader> pModelShader;
    
    DataHandler data;
    
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    float yAngle = 15.0f;
    float xAngle = -5.0f;
    

    std::string vertexShaderFileName = "ModelVertexShader.glsl";
    std::string fragmentShaderFileName = "ModelFragmentShader.glsl";
    std::string vertexLightFileName = "LightModelVertex.glsl";
    std::string fragmentLightFileName = "LightModelFragment.glsl";
    
    MessageType message = MessageType::SUCCESS;
};

#endif // !MATERIAL_H
