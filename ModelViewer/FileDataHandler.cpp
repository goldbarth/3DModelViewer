#include <stb/stb_image.h>
#include <fstream>
#include <fstream>
#include <sstream>
#include <vector>

#include "FileDataHandler.h"


std::string FileDataHandler::ReadFile(const char* pFilePath)
{
    std::ifstream fileStream(pFilePath, std::ios::in);

    if(!fileStream.is_open())
    {
        errorType = ErrorType::READ_FILE_FAILED;
        ErrorHandler::LogError(errorType, "File: " + std::string(pFilePath) + " could not be opened.", __FILE__, __LINE__);
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
        errorType = ErrorType::FILESTREAM_STILL_OPEN;
        ErrorHandler::LogError(errorType, "File: " + std::string(pFilePath) + " was not closed correctly and is still open.", __FILE__, __LINE__);
        return {};
    }
    return data;
}

void FileDataHandler::WriteFile(const char* pFilePath, const char* pData)
{
    
}

std::vector<unsigned char> FileDataHandler::LoadImage(const std::string& filePath, int& width, int& height,
    int& nrChannels)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        ErrorHandler::LogError(ErrorType::READ_FILE_FAILED, "File: " + filePath + " could not be opened.", __FILE__, __LINE__);
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

    ErrorHandler::LogError(ErrorType::FAILED_LOAD_TEXTURE, __FILE__, __LINE__);
    return { std::vector<unsigned char>() };
}
