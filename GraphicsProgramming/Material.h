#ifndef MATERIAL_H
#define MATERIAL_H

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
    Material(FileDataHandler* pData, const char* pFolderPath, const char* pVertexShaderName, const char* pFragmentShaderName)
            : pShaderProgram(new unsigned int(EMPTY)) // pData(pData),
    {
        if (pData == nullptr) return;

        const std::string vertexShaderPath = std::string(pFolderPath) + std::string(pVertexShaderName);
        const std::string fragmentShaderPath = std::string(pFolderPath) + std::string(pFragmentShaderName);

        pVertexShaderSource = strdup(pData->ReadFile(vertexShaderPath.c_str()).c_str());
        pFragmentShaderSource = strdup(pData->ReadFile(fragmentShaderPath.c_str()).c_str());
    }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;
    
    unsigned int* GetShaderProgram() const { return pShaderProgram; }
    
private:
    const int SOURCE_COUNT = 1;
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