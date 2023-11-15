#include <fstream>

#include "FileDataHandler.h"

std::string DataManager::ReadFile(const char* pFilePath)
{
    std::ifstream fileStream(pFilePath, std::ios::in);

    if(!fileStream.is_open())
    {
        errorType = ErrorType::READ_FILE_FAILED;
        ErrorHandler::LogError(errorType, "File: " + std::string(pFilePath) + " could not be opened.", __FILE__, __LINE__);
        return "";
    }

    std::string data;
    std::string line;
    
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        data.append(line + "\n");
    }

    fileStream.close();

    if (fileStream.is_open())
    {
        errorType = ErrorType::FILESTREAM_STILL_OPEN;
        ErrorHandler::LogError(errorType, "File: " + std::string(pFilePath) + " was not closed correctly and is still open.", __FILE__, __LINE__);
        return "";
    }
    return data;
}

void DataManager::WriteFile(const char* pFilePath, const char* pData)
{
    
}
