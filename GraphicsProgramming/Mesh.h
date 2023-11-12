#ifndef MESH_H
#define MESH_H

#include "ErrorHandler.h"
#include "IObject.h"

class Mesh : public IObject
{
public:
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

private:
    ErrorType errorType = ErrorType::SUCCESS;
    
    unsigned int VAO = 0;
    unsigned int VBO = 0;
};

#endif // !MESH_H