#include "FileSystem.h"

#include <stb/stb_image.h>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <fstream>
#include <sstream>
#include <vector>
namespace fs = std::filesystem;

std::string FileSystem::ReadFile(const char* pFilePath)
{
    std::ifstream fileStream(pFilePath, std::ios::in);

    if(!fileStream.is_open())
    {
        message = MessageType::READ_FILE_FAILED;
        ErrorHandler::LogError(message, "File: " + std::string(pFilePath) + " could not be opened.", __FILE__, __LINE__);
        return {};
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
        message = MessageType::FILESTREAM_STILL_OPEN;
        ErrorHandler::LogError(message, "File: " + std::string(pFilePath) + " was not closed correctly and is still open.", __FILE__, __LINE__);
        return {};
    }
    return data;
}

std::string FileSystem::ReadData(const char* shaderFilePath)
{
    std::ifstream fileStream(shaderFilePath, std::ios::in);
    std::string shaderData;
    
    if(fileStream.is_open())
    {
        std::string line;
        while(std::getline(fileStream, line))
        {
            shaderData += line + "\n";
        }
        fileStream.close();
    }
    else
    {
        message = MessageType::READ_FILE_FAILED;
        ErrorHandler::LogError(message, "File: " + std::string(shaderFilePath) + " could not be opened.", __FILE__, __LINE__);
    }
    return shaderData;
}

ShaderData FileSystem::LoadShaderFiles(const char* vertexFilePath, const char* fragmentFilePath)
{
    ShaderData shaderData;
    
    shaderData.vertexData = ReadData(vertexFilePath);
    shaderData.fragmentData = ReadData(fragmentFilePath);

    return shaderData;
}

std::string FileSystem::GetExecutablePath()
{
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);
    return std::string{path};
}

std::string FileSystem::GetResourcePath(const std::string& relativePath)
{
    fs::path exePath(GetExecutablePath());
    fs::path resourcePath = exePath.parent_path().parent_path().parent_path(); // Jump to the working directory
    resourcePath /= "ModelViewer/Resources/"; // Add the relative path to the resource path
    resourcePath /= relativePath;
    return resourcePath.string();
}

std::vector<unsigned char> FileSystem::LoadImg(const std::string& filePath, int& width, int& height, int& nrChannels)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        ErrorHandler::LogError(MessageType::READ_FILE_FAILED, "File: " + filePath + " could not be opened.", __FILE__, __LINE__);
        return { std::vector<unsigned char>() };
    }

    // Read the file into a buffer
    std::ostringstream buffer;
    buffer << file.rdbuf();

    
    // Flip the image vertically and load the image data
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* imageData = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(buffer.str().data()),
        static_cast<int>(buffer.str().size()), &width, &height, &nrChannels, 0);

    if (imageData)
    {
        // Convert the loaded data to a vector
        std::vector result(imageData, imageData + (width * height * nrChannels));

        // Free the original image data
        stbi_image_free(imageData);

        return result;
    }

    ErrorHandler::LogError(MessageType::FAILED_LOAD_TEXTURE, __FILE__, __LINE__);
    return { std::vector<unsigned char>() };
}