#ifndef MODEL_MESH_H
#define MODEL_MESH_H

#include <vector>

#include "ErrorHandler.h"
#include "MeshData.h"
#include "Shader.h"



class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
    : vertices(vertices), indices(indices), textures(textures)
    {
        Initialize();
    }
    
    int Initialize();
    [[nodiscard]] int Draw(const Shader &shader) const;

    // Vertex array object
    
    unsigned int VAO;

private:
    // Vertex buffer object and element buffer object
    
    unsigned int VBO;
    unsigned int EBO;

    // Mesh data

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    MessageType message = MessageType::SUCCESS;
};
#endif