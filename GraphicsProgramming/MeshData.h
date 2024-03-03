#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    
    // Bone indexes which will influence this vertex
    int boneIDs[MAX_BONE_INFLUENCE];
    // Weights from each bone
    float weights[MAX_BONE_INFLUENCE];
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