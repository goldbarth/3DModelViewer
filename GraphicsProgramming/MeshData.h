#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Texture
{
    unsigned int ID;
    std::string type;
    std::string path;
};

struct Transform
{
    glm::vec3 position;
    glm::vec3 scale;
    
    // glm::vec3 rotation;
};


#endif // !MESH_DATA_H