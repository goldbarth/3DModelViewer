#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

int Camera::Initialize()
{
    return 0;
}


int Camera::Update()
{
    viewMatrix = lookAt(position, position + orientation, up);
    projectionMatrix = glm::perspective(glm::radians(cameraData.fovDegree), static_cast<float>(width / height), cameraData.nearPlane, cameraData.farPlane);
    
    return 0;
}

int Camera::Draw()
{
    // Projection matrix to be used in the shader (perspective)
    glUniformMatrix4fv(glGetUniformLocation(*cameraData.pShaderID, cameraData.pUniformName), COUNT, GL_FALSE, value_ptr(projectionMatrix * viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(*cameraData.pShaderID, "projection"), COUNT, GL_FALSE, value_ptr(projectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(*cameraData.pShaderID, "view"), COUNT, GL_FALSE, value_ptr(projectionMatrix));
    
    return 0;
}

void Camera::Finalize()
{
}
