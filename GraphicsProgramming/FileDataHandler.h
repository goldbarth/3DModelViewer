#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <string>

#include "ErrorHandler.h"

class DataManager
{
public:
    std::string ReadFile(const char* pFilePath);
    void WriteFile(const char* pFilePath, const char* pData);

    [[nodiscard]] const char* GetShaderFolderPath() { return "Resource Files/Shader/"; }
    [[nodiscard]] ErrorType GetErrorType() const { return errorType; }

private:
    ErrorType errorType = ErrorType::SUCCESS;
};

#endif // !DATA_MANAGER_H
