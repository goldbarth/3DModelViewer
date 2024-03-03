#include "Textures.h"

#include <stb/stb_image.h>

#include "ErrorHandler.h"

int Textures::LoadAndCreateTexture(unsigned int texture, const std::string &texturePath)
{
    int width;
    int height;
    int nrChannels;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Flip the texture on the y-axis
    stbi_set_flip_vertically_on_load(true);

    // Load the texture data
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        message = MessageType::FAILED_LOAD_TEXTURE;
        ErrorHandler::LogError(message, __FILE__, __LINE__);
        return static_cast<int>(message);
    }
    
    stbi_image_free(data);


    return static_cast<int>(message);
}

int Textures::Update()
{
    return 0;
}

int Textures::Draw()
{
    // Bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    return static_cast<int>(message);
}


int Textures::Initialize()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    const std::string texture1Path = file.GetResourcePath(std::string(file.GetTextureFolderPath()) + texture1FileName);
    const std::string texture2Path = file.GetResourcePath(std::string(file.GetTextureFolderPath()) + texture2FileName);
    LoadAndCreateTexture(texture1, texture1Path);
    LoadAndCreateTexture(texture2, texture2Path);
    
    return static_cast<int>(message);
}


