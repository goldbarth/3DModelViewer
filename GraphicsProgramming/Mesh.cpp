#include <glad/glad.h>

#include "Mesh.h"


int Mesh::Initialize()
{
    // Generate and bind the Vertex Array and Vertex Buffer Objects (VBO)
    glGenVertexArrays(BUFFER_SIZE, pVBO);
    glBindVertexArray(*pVBO);
    glGenBuffers(BUFFER_SIZE, pVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *pVBO);

    // Generate and bind the Element Buffer Object (EBO)
    glGenBuffers(BUFFER_SIZE, pEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pEBO);

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
    
    return static_cast<int>(errorType);
}

void Mesh::Finalize()
{
    if(pEBO != nullptr) glDeleteBuffers(BUFFER_SIZE, pEBO);
    if(pVBO != nullptr) glDeleteVertexArrays(BUFFER_SIZE, pVBO);
}

int Mesh::Update()
{
    return static_cast<int>(errorType);
}

int Mesh::Draw()
{
    glBindVertexArray(*pVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *pEBO);
    
    glDrawArrays(GL_TRIANGLES, VERTEX_ATTRIBUTE_INDEX, static_cast<int>(vertices.size()));
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, reinterpret_cast<void*>(EMPTY));
    
    return static_cast<int>(errorType);
}
