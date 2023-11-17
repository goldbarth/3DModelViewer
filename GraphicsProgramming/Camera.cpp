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
    const auto viewMatrix = lookAt(position, orientation + position, up);
    const auto projectionMatrix = glm::perspective(glm::radians(cameraData.fovDegree), static_cast<float>(width / height), cameraData.nearPlane, cameraData.farPlane);
    
    // Projection matrix to be used in the shader (perspective)
    glUniformMatrix4fv(glGetUniformLocation(*cameraData.pShaderID, cameraData.pUniformName), COUNT, GL_FALSE, value_ptr(projectionMatrix * viewMatrix));
    
    return 0;
}

int Camera::Draw()
{
    return 0;
}
