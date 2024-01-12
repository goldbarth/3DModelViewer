#ifndef CUSTOM_STRUCTS_H
#define CUSTOM_STRUCTS_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

#include "Color.h"
#include "TexCoords.h"
#include "VertPos.h"

struct Vertex
{
    VertPos position;
    TexCoords texCoords;
    Color color;

    Vertex(const VertPos& pos, const TexCoords& texC, const Color& col)
        : position(pos), texCoords(texC), color(col) { }
};

struct Texture
{
    unsigned int ID;
    // std::string type;
    std::string path;
};

struct CameraData
{
    GLfloat fovDegree;
    GLfloat nearPlane;
    GLfloat farPlane;
    
    unsigned int* pShaderID;
    const char* pUniformName;
};

struct Transform
{
    glm::vec3 position;
    glm::vec3 scale;
    
    // glm::vec3 rotation;
};

#endif //!CUSTOM_STRUCTS_H
