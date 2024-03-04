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
    int Draw(const Shader &shader) const;
    
    unsigned int VAO;

private:
    // render data 
    unsigned int VBO;
    unsigned int EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    MessageType message = MessageType::SUCCESS;
};
#endif