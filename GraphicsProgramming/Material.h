#ifndef MATERIAL_H
#define MATERIAL_H

#include "ErrorHandler.h"
#include "IObject.h"

class Material : public IObject
{
public:
    Material(const char* pVertexShader, const char* pFragmentShader)
            : pVertexShaderSource(pVertexShader), pFragmentShaderSource(pFragmentShader),
                pShaderProgram(new unsigned int(EMPTY)) { }
    
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

protected:
    [[nodiscard]] unsigned int GetShaderProgram() const { return *pShaderProgram; }

private:
    const int EMPTY = 0;

    const char* pVertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\n\0";

    const char* pFragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    ErrorType errorType = ErrorType::SUCCESS;

    unsigned int* pShaderProgram = nullptr;
};

#endif // !MATERIAL_H