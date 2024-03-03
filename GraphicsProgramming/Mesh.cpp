#include "ErrorHandler.h"
#include "Mesh.h"


int Mesh::Initialize()
{
    // Generate Vertex Array Objects (VAO)
    glGenVertexArrays(BUFFER_SIZE, pVAO.get());
    
    // Generate Vertex Buffer Objects (VBO)
    glGenBuffers(BUFFER_SIZE, pVBO.get());

    // Generate Element Buffer Objects (EBO)
    glGenBuffers(BUFFER_SIZE, pEBO.get());

    // Bind the VAO first, then bind and set VBOs and then configure vertex attributes
    glBindVertexArray(*pVAO);

    // Now bind the VBO to the VAO
    glBindBuffer(GL_ARRAY_BUFFER, *pVBO);

    // Copy the vertices array in a buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

    // Now bind the EBO to the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pEBO);

    // Copy the indices array in a buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    // Set the vertex position attribute
    glVertexAttribPointer(VERTEX_ATTRIBUTE_INDEX_ZERO, VERTEX_ATTRIBUTE_SIZE, GL_FLOAT, GL_FALSE, VERTEX_ATTRIBUTE_SPACE * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(VERTEX_ATTRIBUTE_INDEX_ZERO);
    
    // Set the vertex color attribute
    glVertexAttribPointer(VERTEX_ATTRIBUTE_INDEX_ONE, VERTEX_ATTRIBUTE_SIZE, GL_FLOAT, GL_FALSE, VERTEX_ATTRIBUTE_SPACE * sizeof(float), reinterpret_cast<void*>(VERTEX_ATTRIBUTE_SIZE * sizeof(float)));
    glEnableVertexAttribArray(VERTEX_ATTRIBUTE_INDEX_ONE);
    
    if (const GLenum error = glGetError(); error != GL_NO_ERROR)
    {
        ErrorHandler::LogError("OpenGL error: " + std::to_string(error), __FILE__, __LINE__);
    }

    glBindVertexArray(*pVAO);
    
    return static_cast<int>(message);
}

int Mesh::Update()
{
    return static_cast<int>(message);
}

int Mesh::Draw()
{
    // glDrawArrays(GL_TRIANGLES, VERTEX_ATTRIBUTE_INDEX_ZERO, 36);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    
    return static_cast<int>(message);
}

void Mesh::Finalize()
{
    if (pEBO) glDeleteBuffers(BUFFER_SIZE, pEBO.get());
    if (pVBO) glDeleteBuffers(BUFFER_SIZE, pVBO.get());
    if (pVAO) glDeleteVertexArrays(BUFFER_SIZE, pVAO.get());
}
