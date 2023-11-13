#ifndef MESH_H
#define MESH_H

#include "ErrorHandler.h"
#include "IObject.h"

class Mesh : public IObject
{
public:
    explicit Mesh(float* pVertices) : pVAO(new unsigned int(0)), pVBO(new unsigned int(0)), pVertices(pVertices) {  }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

private:
    ErrorType errorType = ErrorType::SUCCESS;
    
    unsigned int* pVAO = nullptr;
    unsigned int* pVBO = nullptr;

    float* pVertices = nullptr;
};

#endif // !MESH_H