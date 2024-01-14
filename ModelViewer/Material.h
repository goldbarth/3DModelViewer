#ifndef MATERIAL_H
#define MATERIAL_H

// Map strdup to _strdup in Windows with a macro.
// Just for fun and in case of cross-platform in the future.
// strdup to _strdup: returns a pointer to the storage location for the copied string.
#ifdef _MSC_VER 
#define strdup _strdup
#endif

#include "Color.h"
#include "FileDataHandler.h"
#include "ErrorHandler.h"
#include "IObject.h"

class Material : public IObject
{
public:
    Material(std::unique_ptr<FileDataHandler> pDataHandler, const char* pFolderPath, const char* pVertexShaderName, const char* pFragmentShaderName)
            : pData(std::move(pDataHandler)), pShaderProgram(new unsigned int(EMPTY))
    {
        if (!pData) return;

        const std::string vertexShaderPath = std::string(pFolderPath) + std::string(pVertexShaderName);
        const std::string fragmentShaderPath = std::string(pFolderPath) + std::string(pFragmentShaderName);

        pVertexShaderSource.reset(strdup(pData->ReadFile(vertexShaderPath.c_str()).c_str()));
        pFragmentShaderSource.reset(strdup(pData->ReadFile(fragmentShaderPath.c_str()).c_str()));
    }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

    void AddUniformVector3(const std::string& name, const Color& color) const;
    
    GLuint* GetShaderProgram() const { return pShaderProgram.get(); }

private:
    const int SOURCE_COUNT = 1;
    const int EMPTY = 0;
    
    std::unique_ptr<FileDataHandler> pData;
    std::unique_ptr<GLuint> pShaderProgram;
    
    std::unique_ptr<char> pVertexShaderSource;
    std::unique_ptr<char> pFragmentShaderSource;
    
    MessageType errorType = MessageType::SUCCESS;
};

#ifdef _MSC_VER
#undef strdup
#endif

#endif // !MATERIAL_H