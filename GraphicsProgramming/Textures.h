#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

#include "ErrorHandler.h"
#include "FileSystem.h"
#include "IObject.h"

class Textures final : public IObject
{
public:
    Textures() = default;

    int Initialize() override;
    int Draw() override;
    int Update() override;
    
    int LoadAndCreateTexture(unsigned texture, const std::string& texturePath);

private:
    FileSystem file;
    
    unsigned int texture1;
    unsigned int texture2;

    std::string texture1FileName = "Abstract_Noise_Pixels.png";
    std::string texture2FileName = "Abstract_Noise_Lines.png";

    MessageType message = MessageType::SUCCESS;
};

#endif // !TEXTURE_H
