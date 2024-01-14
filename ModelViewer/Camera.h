#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

#include "CustomStructs.h"
#include "IObject.h"


class Camera : public IObject
{
public:
    Camera(const int& cameraWidth, const int& cameraHeight, const glm::vec3& cameraPosition, const glm::vec3& cameraOrientation, const glm::vec3& cameraUp)
            : width(cameraWidth), height(cameraHeight), position(cameraPosition), orientation(cameraOrientation), up(cameraUp){ }

    void SetCameraData(const CameraData& data) { cameraData = data; }
    void SetPosition(const glm::vec3& pos) { position = pos; }
    void TranslatePosition(const glm::vec3& pos) { position += pos; }
    
    int Initialize() override;
    int Update() override;
    int Draw() override;
    void Finalize() override;

private:
    const int COUNT = 1;
    
    int width = 0;
    int height = 0;

    glm::vec3 position = {};
    glm::vec3 orientation = {};
    glm::vec3 up = {};
    
    CameraData cameraData = {};
    
    glm::mat4x4 viewMatrix = {};
    glm::mat4x4 projectionMatrix = {};
};

#endif // !CAMERA_H
