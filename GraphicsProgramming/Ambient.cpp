#include <glad/glad.h>

#include "ErrorHandler.h"
#include "Ambient.h"


int Ambient::Initialize()
{
    return Material::Initialize();
}

void Ambient::Finalize()
{
    Material::Finalize();
}

int Ambient::Update()
{
    return Material::Update();
}

int Ambient::Draw()
{
    const GLuint lightColorLocation = glGetUniformLocation(reinterpret_cast<GLuint>(GetShaderProgram()), "ambientVector");
    if (lightColorLocation != GL_INVALID_INDEX)
        glUniform3f(static_cast<GLint>(lightColorLocation), lightColor.x, lightColor.y, lightColor.z);
    else
    {
        ErrorHandler::LogError(ErrorType::DRAW_AMBIENT_FAILED, "This could be due to a typo in the uniform variable name "
                                                               "or the shader program might not be linked correctly.", __FILE__, __LINE__);
    }
    
    return Material::Draw();
}
