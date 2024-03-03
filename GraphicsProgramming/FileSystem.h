﻿// Added a file loader function to load images.

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <filesystem>
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
    std::string ReadData(const char* filePath);
    ShaderData LoadShaderFiles(const char* vertexFilePath, const char* fragmentFilePath);
    std::string GetExecutablePath();
    std::string GetResourcePath(const std::string& relativePath);

    static std::vector<unsigned char> LoadImg(const std::string& filePath, int& width, int& height, int& nrChannels);

    const char* GetResourceFolderPath() const { return resourcesFolderPath.c_str(); }
    const char* GetShaderFolderPath() const { return shaderFolderPath.c_str(); }
    const char* GetTextureFolderPath() const { return textureFolderPath.c_str(); }
    const char* GetModelFolderPath() const { return modelFolderPath.c_str(); }
    
    MessageType GetErrorType() const { return message; }

private:
    std::string resourcesFolderPath = "Resources/";
    std::string shaderFolderPath = "Shader/";
    std::string textureFolderPath = "Texture/";
    std::string modelFolderPath = "Models/";
    
    std::filesystem::path relativeResourcePath = "GraphicsProgramming/Resources/";
    
    MessageType message = MessageType::SUCCESS;
};

#endif // !FILE_SYSTEM_H
