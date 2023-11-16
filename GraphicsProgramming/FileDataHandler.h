﻿#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <string>

#include "ErrorHandler.h"

class DataManager
{
public:
    std::string ReadFile(const char* pFilePath);
    void WriteFile(const char* pFilePath, const char* pData);

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
