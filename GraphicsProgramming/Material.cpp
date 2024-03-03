#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "FileSystem.h"
#include "Material.h"

int Material::Initialize()
{
    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    
    const std::string vertexShaderPath = file.GetResourcePath(std::string(file.GetShaderFolderPath()) + vertexShaderFileName);
    const std::string fragmentShaderPath = file.GetResourcePath(std::string(file.GetShaderFolderPath()) + fragmentShaderFileName);
    auto [vertexData, fragmentData] = file.LoadShaderFiles(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    pShader->Compile(vertexData.c_str(), fragmentData.c_str());
    
    return static_cast<int>(message);
}

int Material::Draw()
{
    // Every shader and rendering call after this point will use this shader program
    pShader->UseProgram();
    
    const glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(1920) / static_cast<float>(1080), 0.1f, 100.0f);
    pShader->SetMat4("projection", projection);
    //
    // camera/view transformation
    constexpr float radius = 10.0f;
    const float camX = static_cast<float>(sin(glfwGetTime()) * radius);
    const float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
    const auto view = lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    pShader->SetMat4("view", view);
    
    // calculate the model matrix for each object and pass it to shader before drawing
    auto model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    const float angle = 20.0f * static_cast<float>(glfwGetTime());
    model = rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    pShader->SetMat4("model", model);
    
    return static_cast<int>(message);
}

void Material::Finalize() const
{
    glDeleteProgram(shaderProgram);
}
