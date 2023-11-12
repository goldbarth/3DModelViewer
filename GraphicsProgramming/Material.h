#ifndef MATERIAL_H
#define MATERIAL_H

#include "ErrorHandler.h"
#include "IObject.h"

class Material : public IObject
{
public:
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

private:
    ErrorType errorType = ErrorType::SUCCESS;

    unsigned int shaderProgram = 0;
    unsigned int VAO = 0;
    unsigned int VBO = 0;
};

#endif // !MATERIAL_H