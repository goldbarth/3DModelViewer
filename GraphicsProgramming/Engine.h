#ifndef ENGINE_H
#define ENGINE_H

#include "Viewport.h"
#include "Material.h"
#include "MeshData.h"
#include "Textures.h"
#include "Mesh.h"

// Engine class (and all other child classes) is final, so it cannot be inherited and used as a base class.
// This is a good practice to prevent misuse of the class and clearly define its purpose.
class Engine : public IObject
{
public:

    Engine() : pViewport(nullptr), pMaterial(nullptr), pMesh(nullptr), pTextures(nullptr) { }
private:
    // GLFW values (versions)

    const int GLFW_MAJOR_VERSION = 3;
    const int GLFW_MINOR_VERSION = 3;

    // Window values

    const int WINDOW_WIDTH = 1080;
    const int WINDOW_HEIGHT = 720;
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
    int Update() override;
    int Draw() override;
    
    int Run();
    void Finalize();

private:
    std::unique_ptr<Viewport> pViewport;
    std::unique_ptr<Material> pMaterial;
    std::unique_ptr<Mesh> pMesh;
    std::unique_ptr<Textures> pTextures;

    // Mesh data

    Color white = Color(1.0f, 1.0f, 1.0f, 1.0f);
    Color red = Color(1.0f, 0.0f, 0.0f, 1.0f);
    Color green = Color(0.0f, 1.0f, 0.0f, 1.0f);
    Color blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
    
    std::vector<Texture> textures = {};

    // Triangle
    // std::vector<float> vertices = std::vector
    // {
    //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    //      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    // };

    // Rectangle
    // std::vector<float> vertices = {
    //     // Positionen       // Farben
    //     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // oben rechts
    //     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // unten rechts
    //    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // unten links
    //    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f    // oben links
    // };

    // Cube
    std::vector<float> vertices =
    {
        // // Positionen         // Farben
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // Back bottom left (Red)
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // Back bottom right (Green)
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // Back top right (Blue)
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // Back top left (Yellow)
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // Front bottom left (Magenta)
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Front bottom right (Cyan)
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front top right (White)
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f  // Front top left (Black)
    };
    
    // std::vector<float> vertices =
    // {
    //     // positions          // colors           // texture coords
    //     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    //     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    // };
    
    // 2D Rectangle
    // std::vector<unsigned int> indices = std::vector<unsigned int>
    // {
    //     0, 1, 3, // first triangle
    //     1, 2, 3 // second triangle
    // };
    
    // 3D Cube
    std::vector<unsigned int> indices =
    {
        // Back
        0, 1, 2, 0, 2, 3,
        // Front
        4, 5, 6, 4, 6, 7,
        // Left
        4, 7, 3, 4, 3, 0,
        // Right
        1, 5, 6, 1, 6, 2,
        // Bottom
        0, 1, 5, 0, 5, 4,
        // Top
        3, 2, 6, 3, 6, 7
    };

    MessageType message = MessageType::SUCCESS;
};

#endif // !ENGINE_H
