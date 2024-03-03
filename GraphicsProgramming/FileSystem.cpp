#include "FileSystem.h"

#include <stb/stb_image.h>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <fstream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

std::string FileSystem::ReadData(const char* filePath)
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

ShaderData FileSystem::LoadShaderFiles(const char* vertexFilePath, const char* fragmentFilePath)
{
    ShaderData shaderData;
    shaderData.vertexData = ReadData(vertexFilePath);
    shaderData.fragmentData = ReadData(fragmentFilePath);

    return shaderData;
}

std::string FileSystem::GetExecutablePath()
{
    char path[MAX_PATH]; // MAX_PATH is a constant defined in windows.h
    GetModuleFileNameA(nullptr, path, MAX_PATH); // Get the path of the executable
    return std::string{path};
}

std::string FileSystem::GetResourcePath(const std::string& relativePath)
{
    const fs::path exePath(GetExecutablePath());
    fs::path resourcePath = exePath.parent_path().parent_path().parent_path(); // Jump to the working directory
    resourcePath /= relativeResourcePath; // Add the relative path to the resource path
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