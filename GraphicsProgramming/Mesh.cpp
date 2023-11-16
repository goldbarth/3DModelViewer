#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Mesh.h"


int Mesh::Initialize()
{
    // Generate and bind the Vertex Array and Vertex Buffer Objects (VBO)
    glGenVertexArrays(BUFFER_SIZE, pVertexBufferObject);
    glBindVertexArray(*pVertexBufferObject);
    glGenBuffers(BUFFER_SIZE, pVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, *pVertexBufferObject);
    
    // Generate and bind the Element Buffer Object (EBO)
    glGenBuffers(BUFFER_SIZE, pElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pElementBufferObject);

    // Copy our vertices array in a buffer for OpenGL to use (Vertex list)
    const GLsizeiptr vectorSizeInBytes = sizeof(vertices) * (sizeof(Vertex) * vertices.size());
    glBufferData(GL_ARRAY_BUFFER, vectorSizeInBytes, vertices.data(), GL_STATIC_DRAW);

    // Copy our indices array in a buffer for OpenGL to use (Index list)
    const GLsizeiptr indexSizeInBytes = sizeof(unsigned int) * indices.size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSizeInBytes, &indices.front(), GL_STATIC_DRAW);

    // Position attribute (Vertex)
    glVertexAttribPointer(VERTEX_ATTRIBUTE_INDEX, GetPositionNumber(), GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(EMPTY));
    glEnableVertexAttribArray(VERTEX_ATTRIBUTE_INDEX);

    // Color attribute (Vertex)
    glVertexAttribPointer(COLOR_ATTRIBUTE_INDEX, GetColorNumber(), GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(GetPositionSize()));
    glEnableVertexAttribArray(COLOR_ATTRIBUTE_INDEX);

    // Texture attribute (Vertex)
    glVertexAttribPointer(TEXTURE_ATTRIBUTE_INDEX, GetTextureNumber(), GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(GetPositionSize() + GetColorSize()));
    glEnableVertexAttribArray(TEXTURE_ATTRIBUTE_INDEX);
    
    // Texture attribute (Vertex)

    if (textures.empty()) return static_cast<int>(errorType);
    
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    for (auto& texture : textures)
    {
        // Load and create a texture
        glGenTextures(TEXTURE_COUNT, &texture.ID);
        glBindTexture(GL_TEXTURE_2D, texture.ID);

        // Set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load image, create texture and generate mipmaps:

        // Tell stb_image.h to flip loaded texture's on the y-axis.
        stbi_set_flip_vertically_on_load(true);

        // Load the image
        unsigned char* pData = stbi_load(texture.path.c_str(), &width, &height, &nrChannels, DEFAULT_CHANNELS);
        if (pData)
        {
            // Create the texture
            glTexImage2D(GL_TEXTURE_2D, MIP_LEVEL, GL_RGB, width, height, BORDER, GL_RGB, GL_UNSIGNED_BYTE, pData);
            // Generate the mipmaps
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            errorType = ErrorType::FAILED_LOAD_TEXTURE;
            ErrorHandler::LogError(errorType, __FILE__, __LINE__);
            return static_cast<int>(errorType);
        }

        stbi_image_free(pData);
    }
    
    return static_cast<int>(errorType);
}

void Mesh::Finalize()
{
    if(pElementBufferObject != nullptr) glDeleteBuffers(BUFFER_SIZE, pElementBufferObject);
    if(pVertexBufferObject != nullptr) glDeleteVertexArrays(BUFFER_SIZE, pVertexBufferObject);
}

int Mesh::Update()
{
    return static_cast<int>(errorType);
}

int Mesh::Draw()
{
    for (int i = 0; i < static_cast<int>(textures.size()); i++)
    {
        // Activate the texture unit first before binding texture
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].ID);
    }
    
    glBindVertexArray(*pVertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pElementBufferObject);
    
    glDrawArrays(GL_TRIANGLES, VERTEX_ATTRIBUTE_INDEX, static_cast<int>(vertices.size()));
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, reinterpret_cast<void*>(EMPTY));
    
    return static_cast<int>(errorType);
}

std::vector<Vertex> Mesh::TranslateVertices(std::vector<Vertex> vertices, const Transform* pTransform)
{
    if (pTransform == nullptr) return vertices;
    for (auto&& vertex : vertices)
    {
        vertex.position.x += pTransform->position.x;
        vertex.position.y += pTransform->position.y;
        vertex.position.z += pTransform->position.z;

        vertex.position.x *= pTransform->scale.x;
        vertex.position.y *= pTransform->scale.y;
        vertex.position.z *= pTransform->scale.z;
    }

    return vertices;
}
