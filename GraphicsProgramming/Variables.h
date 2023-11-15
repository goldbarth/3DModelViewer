#ifndef VARIABLES_H
#define VARIABLES_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Color.h"

struct Vertex
{
    glm::vec3 position;
    Color color;

    Vertex(const glm::vec3& pos, const Color& col)
        : position(pos), color(col) {}
};

struct CameraData
{
    float fovDegree;
    float nearPlane;
    float farPlane;
    
    unsigned int* pShaderID;
    const char* pUniformName;
    
};

#endif //!VARIABLES_H
