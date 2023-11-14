#ifndef MATERIAL_H
#define MATERIAL_H

// Just playing around with the preprocessor directives.
// Map strdup to _strdup in Windows with a macro.
// Just for fun and in case of cross-platform in the future.
// strdup to _strdup: returns a pointer to the storage location for the copied string.
#ifdef _MSC_VER 
#define strdup _strdup
#endif

#include "FileDataHandler.h"
#include "ErrorHandler.h"
#include "IObject.h"

class Material : public IObject
{
public:
    Material(DataManager* pData, const char* pVertexShader, const char* pFragmentShader)
            : pShaderProgram(new unsigned int(EMPTY)) // pData(pData),
    {
        if(pData == nullptr) return;
        pVertexShaderSource = strdup(pData->ReadFile(pVertexShader).c_str());
        pFragmentShaderSource = strdup(pData->ReadFile(pFragmentShader).c_str());
    }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

protected:
    [[nodiscard]] unsigned int GetShaderProgram() const { return *pShaderProgram; }

private:
    const int EMPTY = 0;
    
    //DataManager* pData = nullptr;
    
    const char* pVertexShaderSource = nullptr;
    const char* pFragmentShaderSource = nullptr;
    
    unsigned int* pShaderProgram = nullptr;
    
    ErrorType errorType = ErrorType::SUCCESS;
};

#ifdef _MSC_VER
#undef strdup
#endif

#endif // !MATERIAL_H