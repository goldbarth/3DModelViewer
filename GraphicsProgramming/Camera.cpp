#include "Camera.h"

glm::mat4 Camera::GetViewMatrix() const
{
    return lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(const CameraMovement direction, const float deltaTime)
{
    const float velocity = movementSpeed * deltaTime;
    glm::vec3 directionVector;
    switch (direction)
    {
        case FORWARD:
            directionVector = front;
            break;
        case BACKWARD:
            directionVector = -front;
            break;
        case LEFT:
            directionVector = -right;
            break;
        case RIGHT:
            directionVector = right;
            break;
    }

    position += directionVector * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, const GLboolean constrainPitch)
{
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw   += xOffset;
    pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
        pitch = glm::clamp(pitch, -89.0f, 89.0f);

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(const float yOffset)
{
    zoom = glm::clamp(zoom - yOffset, 1.0f, 45.0f);
}

void Camera::UpdateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 frontVector;
    frontVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVector.y = sin(glm::radians(pitch));
    frontVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    // normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    front = normalize(frontVector);
    right = normalize(cross(frontVector, worldUp));
    up    = normalize(cross(right, frontVector));
}
