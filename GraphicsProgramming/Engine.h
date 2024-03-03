#ifndef ENGINE_H
#define ENGINE_H

#include "Viewport.h"
#include "Material.h"
#include "Mesh.h"

// Engine class (and all other child classes) is final, so it cannot be inherited and used as a base class.
// This is a good practice to prevent misuse of the class and clearly define its purpose.
class Engine : public IObject
{
public:

    Engine() : pViewport(nullptr), pMaterial(nullptr), pModel(nullptr) { }
private:
    // GLFW values

    const int GLFW_MAJOR_VERSION = 3;
    const int GLFW_MINOR_VERSION = 3;

    // Window values

    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;
    const int WINDOW_OFFSET_X = 0;
    const int WINDOW_OFFSET_Y = 0;

    const std::string WINDOW_TITLE = "Glodbarth Engine 1.0";

    // Colors

    const Color BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
    const Color TURQUOISE = Color(0.0f, 0.5f, 0.5f, 1.0f);
    const Color DARK_GRAY = Color(0.25f, 0.25f, 0.25f, 1.0f);
    const Color LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f, 1.0f);
    
public:
    bool InitializeObjects();
    
    int Initialize() override;
    int Draw() override;
    
    int Run();
    void Finalize() const;

private:
    std::unique_ptr<Viewport> pViewport;
    std::unique_ptr<Material> pMaterial;
    std::unique_ptr<Model> pModel;

    FileSystem fileSystem;

    std::string vertexShaderFileName = "ModelVertexShader.glsl";
    std::string fragmentShaderFileName = "ModelFragmentShader.glsl";
    std::string modelPathAndFileName = "Backpack/backpack.obj";

    std::string absoluteModelPath = fileSystem.GetResourcePath(std::string(fileSystem.GetModelFolderPath()) + modelPathAndFileName);

    MessageType message = MessageType::SUCCESS;
};

#endif // !ENGINE_H
