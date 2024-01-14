// Added a file loader function to load images.

#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <string>

#include "ErrorHandler.h"

class FileDataHandler
{
public:
    std::string ReadFile(const char* pFilePath);
    void WriteFile(const char* pFilePath, const char* pData);

    static std::vector<unsigned char> LoadImage(const std::string& filePath, int& width, int& height, int& nrChannels);

    const char* GetShaderFolderPath() const { return pShaderFolderPath.c_str(); }
    void SetShaderFolderPath(const char* pFolderPath) { pShaderFolderPath = pFolderPath; }

    const char* GetTextureFolderPath() const { return pTextureFolderPath.c_str(); }
    void SetTextureFolderPath(const char* pFolderPath) { pTextureFolderPath = pFolderPath; }
    
    ErrorType GetErrorType() const { return errorType; }

private:
    std::string pShaderFolderPath = "Resource Files/Shader/";
    std::string pTextureFolderPath = "Resource Files/Texture/";
    
    ErrorType errorType = ErrorType::SUCCESS;
};

#endif // !DATA_MANAGER_H
