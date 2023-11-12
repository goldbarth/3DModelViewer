#include <glad/glad.h>

#include "Mesh.h"


int Mesh::Initialize()
{
    float vertices[] =
    {
        -0.9f, -0.5f, 0.0f, // left
        0.0f, -0.5f, 0.0f, // right
        -0.45f,  0.5f, 0.0f, // top

        // 2. Triangle
        0.0f, -0.5f, 0.0f, // left
        0.9f, -0.5f, 0.0f, // right
        0.45f,  0.5f, 0.0f, // top
        
    };

    VBO = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return static_cast<int>(errorType);
}

void Mesh::Finalize()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

int Mesh::Update()
{
    glBindVertexArray(VAO);
    
    return static_cast<int>(errorType);
}

int Mesh::Draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    return static_cast<int>(errorType);
}
