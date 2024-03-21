#ifndef ENGINE_H
#define ENGINE_H

#include "Camera.h"
#include "DataHandler.h"
#include "Viewport.h"
#include "Material.h"
#include "Model.h"

// Engine class (and all other child classes) is final, so it cannot be inherited and used as a base class.
// This is a good practice to prevent misuse of the class and clearly define its purpose.
class Engine final : public IObject
{
public:

    Engine() : pViewport(nullptr), pMaterial(nullptr), pCamera(nullptr), pModel(nullptr) { }
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

    // Background colors

    const Color BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
    const Color TURQUOISE = Color(0.0f, 0.5f, 0.5f, 1.0f);
    const Color DARK_GRAY = Color(0.25f, 0.25f, 0.25f, 1.0f);
    const Color LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f, 1.0f);
    
public:
    bool InitializeObjects();
    
    int Initialize() override;
    void Finalize() const override;

    int Run();

private:
    std::unique_ptr<Viewport> pViewport;
    std::unique_ptr<Material> pMaterial;
    std::unique_ptr<Camera> pCamera;
    std::unique_ptr<Model> pModel;

    DataHandler data;

    // File names
    
    std::string vertexShaderFileName = "LightModelVertex.glsl";
    std::string fragmentShaderFileName = "LightModelFragment.glsl";
    std::string modelPathAndFileName = "Backpack/backpack.obj";
    
    std::string absoluteModelPath = data.GetResourcePath(std::string(data.GetModelFolderPath()) + modelPathAndFileName);

    MessageType message = MessageType::SUCCESS;
};

#endif // !ENGINE_H
