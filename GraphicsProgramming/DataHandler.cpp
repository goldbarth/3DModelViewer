#include "DataHandler.h"

#include <stb/stb_image.h>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <fstream>

std::string DataHandler::ReadData(const char* filePath)
{
    std::ifstream fileStream(filePath, std::ios::in);
    std::string data;
    
    if(fileStream.is_open())
    {
        std::string line;
        // Precise way to read the file.
        // Prevents invalid reads from being carried out after the end of the file has been reached.
        while(std::getline(fileStream, line))
        {
            data += line + "\n";
        }
        fileStream.close();
    }
    else
    {
        message = MessageType::READ_FILE_FAILED;
        ErrorHandler::LogError(message, "File: " + std::string(filePath) + " could not be opened.", __FILE__, __LINE__);
    }
    return data;
}

std::string DataHandler::GetExecutablePath()
{
    char path[MAX_PATH]; // MAX_PATH is a constant defined in windows.h
    GetModuleFileNameA(nullptr, path, MAX_PATH); // Get the path of the executable
    return std::string{path};
}

/// <summary>
/// QOL function to get the executable path and change it to the relative path to the resource folder.
/// To always access the folder in the ide or exe. There you go.
/// </summary>
std::string DataHandler::GetResourcePath(const std::string& relativePath)
{
    const std::filesystem::path exePath(GetExecutablePath());
    std::filesystem::path resourcePath = exePath.parent_path().parent_path().parent_path(); // Jump to the working directory
    resourcePath /= relativeResourcePath; // Add the relative path to the resource path
    resourcePath /= relativePath;
    return resourcePath.string();
}

ShaderData DataHandler::LoadShaderFiles(const char* vertexFilePath, const char* fragmentFilePath)
{
    ShaderData shaderData;
    shaderData.vertexData = ReadData(vertexFilePath);
    shaderData.fragmentData = ReadData(fragmentFilePath);

    return shaderData;
}
