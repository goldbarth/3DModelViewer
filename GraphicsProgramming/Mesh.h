﻿#ifndef MESH_H
#define MESH_H

#include <vector>

#include "ErrorHandler.h"
#include "Variables.h"
#include "IObject.h"

class Mesh : public IObject
{
public:
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) : vertices(vertices), indices(indices),
                    pVAO(new unsigned int(EMPTY)), pVBO(new unsigned int(EMPTY)), pEBO(new unsigned int(EMPTY)) {  }
private:
    // Bytes
    [[nodiscard]] constexpr int GetPositionSize() const { return sizeof(glm::vec3); }

    // Numbers
    [[nodiscard]] constexpr int GetPositionNumber() const { return sizeof(glm::vec3) / sizeof(float); }
    [[nodiscard]] constexpr int GetColorNumber() const { return sizeof(glm::vec4) / sizeof(float); }
    
public:
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

private:
    const int EMPTY = 0;
    const int BUFFER_SIZE = 1;
    const int VERTEX_ATTRIBUTE_INDEX = 0;
    const int COLOR_ATTRIBUTE_INDEX = 0;
    
    std::vector<Vertex> vertices = {};
    std::vector<unsigned int> indices = {};
    
    unsigned int* pVAO = nullptr;
    unsigned int* pVBO = nullptr;
    unsigned int* pEBO = nullptr;

    
    ErrorType errorType = ErrorType::SUCCESS;
};

#endif // !MESH_H