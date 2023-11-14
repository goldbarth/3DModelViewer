﻿#ifndef AMBIENT_H
#define AMBIENT_H

#include <glm/vec3.hpp>

#include "Material.h"

class Ambient : public Material
{
public:
    Ambient(DataManager* pData, const char* pVertexShader, const char* pFragmentShader)
            : Material(pData, pVertexShader, pFragmentShader) { }

    [[nodiscard]] glm::vec3 GetLightColor() const { return lightColor; }
    void SetLightColor(const glm::vec3& color) { this->lightColor = color; }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;
    
private:
    glm::vec3 lightColor = {};
    
};

#endif // !AMBIENT_H