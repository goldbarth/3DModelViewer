#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "ErrorHandler.h"
#include "DataHandler.h"
#include "IObject.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

class Material final : public IObject
{
public:
    Material(std::string vertexShaderName, std::string fragmentShaderName)
                : pModelShader(std::make_unique<Shader>()), vertexShaderFileName(std::move(vertexShaderName)),
                    fragmentShaderFileName(std::move(fragmentShaderName))
    {} 
    
    int Initialize() override;
    int Draw() override;
    void Finalize() const override;
    int Update(const Camera* camera);
    
    Shader* GetModelShader() const { return pModelShader.get(); }
    
    Model* SetModel(Model* aModel) { return pModel = aModel; }

    float GetObjectAngle() const { return yAngle; }
    void SetObjectYaw(const float aAngle) { this->yAngle = aAngle; }
    float GetObjectPitch() const { return xAngle; }
    void SetObjectPitch(const float aAngle) { this->xAngle = aAngle; }


private:
    std::unique_ptr<Shader> pModelShader;
    Model* pModel;
    
    DataHandler data;
    
    // Colors
    
    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f); // Orange (Beige?)
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // White

    // Positions
    
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f); // Light position
    glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, 3.0f); // Camera position
    glm::vec3 pivotPos = glm::vec3(0.0f, 0.0f, 0.0f);
     // Angles
    
    float yAngle = 15.0f; // Yaw
    float xAngle = -5.0f; // Pitch

    // File names
    
    std::string vertexShaderFileName;
    std::string fragmentShaderFileName;
    
    MessageType message = MessageType::SUCCESS;
};

#endif // !MATERIAL_H
