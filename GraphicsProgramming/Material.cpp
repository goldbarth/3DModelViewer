#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Material.h"

int Material::Initialize()
{
    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    
    const std::string vertexShaderPath = data.GetResourcePath(std::string(data.GetShaderFolderPath()) + vertexLightFileName);
    const std::string fragmentShaderPath = data.GetResourcePath(std::string(data.GetShaderFolderPath()) + fragmentLightFileName);
    auto [vertexData, fragmentData] = data.LoadShaderFiles(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    pModelShader->Compile(vertexData.c_str(), fragmentData.c_str());
    
    return static_cast<int>(message);
}

int Material::Draw()
{
    pModelShader->UseProgram();
    
    return static_cast<int>(message);
}

void Material::Finalize() const
{
}

int Material::Update(const Camera *camera)
{
    lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
    lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
    pModelShader->SetVec3("objectColor", objectColor);
    pModelShader->SetVec3("lightColor", lightColor);
    pModelShader->SetVec3("lightPos", lightPos);
    pModelShader->SetVec3("viewPos", viewPos);

    const glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), static_cast<float>(1920) / static_cast<float>(1080), 0.1f, 100.0f);
    pModelShader->SetMat4("projection", projection);
    
    const auto view = camera->GetViewMatrix();
    pModelShader->SetMat4("view", view);
    
    glm::mat4 model = glm::mat4(1.0f);
    
    // Model position (Pivot point)
    model = translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    
    // Rotate yaw and pitch
    model = rotate(model, glm::radians(yAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = rotate(model, glm::radians(xAngle), glm::vec3(1.0f, 0.0f, 0.0f));
    pModelShader->SetMat4("model", model);
    
    return static_cast<int>(message);
}

