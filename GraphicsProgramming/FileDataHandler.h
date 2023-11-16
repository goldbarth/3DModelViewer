#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <string>

#include "ErrorHandler.h"

class DataManager
{
public:
    std::string ReadFile(const char* pFilePath);
    void WriteFile(const char* pFilePath, const char* pData);

    const char* GetShaderFolderPath() const { return pFolderPath.c_str(); }
    ErrorType GetErrorType() const { return errorType; }

private:
    std::string pFolderPath = "Resource Files/Shader/";
    
    ErrorType errorType = ErrorType::SUCCESS;
};

#endif // !DATA_MANAGER_H
