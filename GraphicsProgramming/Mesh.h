#ifndef MESH_H
#define MESH_H

#include <glm/vec3.hpp>
#include <vector>

#include "ErrorHandler.h"
#include "IObject.h"

class Mesh : public IObject
{
public:
    explicit Mesh(const std::vector<glm::vec3>& pVertices) : pVAO(new unsigned int(EMPTY)),
                    pVBO(new unsigned int(EMPTY)), pVertices(pVertices) {  }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

private:
    const int EMPTY = 0;
    
    unsigned int* pVAO = nullptr;
    unsigned int* pVBO = nullptr;

    std::vector<glm::vec3> pVertices = {};
    
    ErrorType errorType = ErrorType::SUCCESS;
};

#endif // !MESH_H