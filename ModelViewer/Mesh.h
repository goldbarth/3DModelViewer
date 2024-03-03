#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <memory>

#include "FileSystem.h"
#include "ErrorHandler.h"
#include "IObject.h"
#include "MeshData.h"
#include "Shader.h"

class Mesh final : public IObject
{
public:
    //Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures){}
    explicit Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) :
        pVBO(std::make_unique<unsigned int>()), pVAO(std::make_unique<unsigned int>()),
        pEBO(std::make_unique<unsigned int>()),
        vertices(vertices), indices(indices) {}
    
private:
    const GLuint EMPTY = 0;
    const GLint VERTEX_ATTRIBUTE_INDEX_ZERO = 0; // attribute: location = vertex shader layout (location = 0) 
    const GLint VERTEX_ATTRIBUTE_INDEX_ONE = 1; // attribute: location = vertex shader layout (location = 1) 
    const GLint VERTEX_ATTRIBUTE_INDEX_TWO = 2; // attribute: location = vertex shader layout (location = 2) 
    const GLint VERTEX_ATTRIBUTE_SIZE = 3; // in vec3 aPos
    const GLsizei BUFFER_SIZE = 1;
    const GLsizei VERTEX_ATTRIBUTE_SPACE = 6; // 3 * sizeof(float)
    const GLsizei VERTICES_COUNT_VBO = 3;
    const GLsizei VERTICES_COUNT_EBO = 6;
    const GLsizei TEXTURE_COUNT = 1;

public:
    int Initialize() override;
    int Update() override;
    int Draw() override;
    void Finalize();
private:
    std::unique_ptr<unsigned int> pVBO;
    std::unique_ptr<unsigned int> pVAO;
    std::unique_ptr<unsigned int> pEBO;


    std::vector<float> vertices = {};
    std::vector<unsigned int> indices = {};
    std::vector<Texture> textures = {};

    FileSystem file;

    unsigned int texture;
    unsigned int texture1;
    unsigned int texture2;

    MessageType message = MessageType::SUCCESS;
};

#endif // !MESH_H
