#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

int Camera::Initialize()
{
    return 0;
}

void Camera::Finalize()
{
}

int Camera::Update()
{
    constexpr auto projectionMatrix = glm::zero<glm::mat4x4>();
    const auto viewMatrix = lookAt(position, orientation + position, up);

    // Projection matrix to be used in the shader (perspective)
    glUniformMatrix4fv(glGetUniformLocation(*cameraData.pShaderID, cameraData.pUniformName), COUNT, GL_FALSE, value_ptr(projectionMatrix * viewMatrix));
    
    // glm::mat4x4 projectionMatrix = glm::perspective(glm::radians(cameraData.fovDegree), (float)width / (float)height, cameraData.nearPlane, cameraData.farPlane);
    
    return 0;
}

int Camera::Draw()
{
    return 0;
}
