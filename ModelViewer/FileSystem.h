// Added a file loader function to load images.

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>

#include "ErrorHandler.h"

struct ShaderData
{
    std::string vertexData;
    std::string fragmentData;
};

class FileSystem
{
public:
    std::string ReadFile(const char* pFilePath);
    std::string ReadData(const char* shaderFilePath);
    ShaderData LoadShaderFiles(const char* vertexFilePath, const char* fragmentFilePath);
    std::string GetExecutablePath();
    std::string GetResourcePath(const std::string& relativePath);

    static std::vector<unsigned char> LoadImg(const std::string& filePath, int& width, int& height, int& nrChannels);

    const char* GetShaderFolderPath() const { return pShaderFolderPath.c_str(); }
    void SetShaderFolderPath(const char* pFolderPath) { pShaderFolderPath = pFolderPath; }

    const char* GetTextureFolderPath() const { return pTextureFolderPath.c_str(); }
    void SetTextureFolderPath(const char* pFolderPath) { pTextureFolderPath = pFolderPath; }
    
    MessageType GetErrorType() const { return message; }

private:
    std::string pShaderFolderPath = "Resource Files/Shader/";
    std::string pTextureFolderPath = "Resource Files/Texture/";
    
    MessageType message = MessageType::SUCCESS;
};

#endif // !FILE_SYSTEM_H
