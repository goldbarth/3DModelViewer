#include <glad/glad.h>

#include "Defines.h"
#include "Mesh.h"


int Mesh::Initialize()
{
    glGenVertexArrays(1, pVAO);
    glGenBuffers(1, pVBO);

    glBindVertexArray(*pVAO);

    glBindBuffer(GL_ARRAY_BUFFER, *pVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pVertices) * (sizeof(float) * GET_ARRAY_PTR_LENGHT(pVertices, float)), &pVertices[0], GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(pVertices) * (sizeof(float) * 18), &pVertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return static_cast<int>(errorType);
}

void Mesh::Finalize()
{
    glDeleteVertexArrays(1, pVAO);
    glDeleteBuffers(1, pVBO);
}

int Mesh::Update()
{
    glBindVertexArray(*pVAO);
    
    return static_cast<int>(errorType);
}

int Mesh::Draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    return static_cast<int>(errorType);
}
