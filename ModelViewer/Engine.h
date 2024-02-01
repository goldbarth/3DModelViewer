#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "FileDataHandler.h"
#include "Viewport.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "TexCoords.h"
#include "VertPos.h"

class Engine
{
public:
    explicit Engine(std::unique_ptr<FileDataHandler> pData) : pData(std::move(pData)) {  }
	
    const CameraData& GetDefaultCameraData() const;
    bool InitializeObjects();
    int Initialize();
    int Run();

private:
    // GLFW values (versions)

    static const int GLFW_MAJOR_VERSION;
    static const int GLFW_MINOR_VERSION;

    // Window values

    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const int WINDOW_OFFSET_X;
    static const int WINDOW_OFFSET_Y;

    static const std::string WINDOW_TITLE;

    // Camera values
    
    static const std::string CAMERA_UNIFORM_NAME;
	
    static const glm::vec3 CAMERA_POSITION;
    static const glm::vec3 CAMERA_ORIENTATION;
    static const glm::vec3 CAMERA_UP;

    static const float DEFAULT_CAMERA_FOV_DEGREE;
    static const float DEFAULT_CAMERA_NEAR;
    static const float DEFAULT_CAMERA_FAR;

    // Input values

    static const glm::vec3 FORWARD_INPUT;
    static const glm::vec3 BACKWARD_INPUT;
    static const glm::vec3 LEFT_INPUT;
    static const glm::vec3 RIGHT_INPUT;

    // Colors
    
    static const Color GOLD;
    static const Color BLACK;
    static const Color TURQUOISE; 
    static const Color DARK_GRAY;
    static const Color LIGHT_GRAY;

	// Uniform values

	static const Color LIGHT_POSITION;
	static const Color LIGHT_COLOR;
	static const Color MATERIAL_COLOR;
	static const Color SPECULAR_COLOR;

    // Pointers
	
	std::unique_ptr<FileDataHandler> pData;
    std::unique_ptr<Camera> pCamera;
    std::unique_ptr<Viewport> pViewport;
    // std::unique_ptr<Material> pPhongMaterial;
	std::unique_ptr<Material> pBlinnPhongMaterial;
	
    std::unique_ptr<Mesh> pMesh;

    // Error handling
    
    MessageType errorType = MessageType::SUCCESS;
    
    // Shader values

	static const std::string AMBIENT_UNIFORM_NAME;
	static const std::string PHONG_LIGHT_POSITION_UNIFORM_NAME;
	static const std::string PHONG_LIGHT_COLOR_UNIFORM_NAME;
	static const std::string PHONG_MATERIAL_COLOR_UNIFORM_NAME;
	static const std::string PHONG_SPECULAR_COLOR_UNIFORM_NAME;

    static const char* pAmbientVertexShaderName;
    static const char* pAmbientFragmentShaderName;
    static const char* pDefaultVertexShaderName;
    static const char* pDefaultFragmentShaderName;
	static const char* pPhongVertexShaderName;
	static const char* pPhongFragmentShaderName;
	static const char* pBlinnPhongVertexShaderName;
	static const char* pBlinnPhongFragmentShaderName;

	// Mesh values
	
	// Vertices
    
    Color white = Color(1.0f, 1.0f, 1.0f, 1.0f);
    Color red = Color(1.0f, 0.0f, 0.0f, 1.0f);
    Color green = Color(0.0f, 1.0f, 0.0f, 1.0f);
    Color blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
    
    std::vector<Vertex> vertices = std::vector
    {
    	// Rectangle:
    	
        // Vertex{VertPos(-0.5f, -0.5f, 0.0f), TexCoords(0.0f, 0.0f), Color(white)}, // left-bottom
        // Vertex{VertPos( 0.5f, -0.5f, 0.0f), TexCoords(1.0f, 0.0f), Color(red)}, // right-bottom
        // Vertex{VertPos(-0.5f, 0.5f, 0.0f), TexCoords(0.0f, 0.1f),Color(green)}, // top-left
        // Vertex{VertPos(0.5f, 0.5f, 0.0f), TexCoords(1.0f, 1.0f),Color(blue)}, // top-right
    	
    	// Cube:
        		// x     y     z						            u     v					nx    ny    nz				r      g     b    a
			Vertex{VertPos(-0.5f, -0.5f, -0.5f), TexCoords(0.0f, 0.0f), Normals(0.0f, 0.0f, -1.0f),Color(white)},
			Vertex{VertPos( 0.5f, -0.5f, -0.5f), TexCoords(1.0f, 0.0f), Normals(0.0f, 0.0f, -1.0f),Color(red)},
			Vertex{VertPos( 0.5f,  0.5f, -0.5f), TexCoords(1.0f, 1.0f), Normals(0.0f, 0.0f, -1.0f),Color(green)},
			Vertex{VertPos( 0.5f,  0.5f, -0.5f), TexCoords(1.0f, 1.0f), Normals(0.0f, 0.0f, -1.0f),Color(blue)},
			Vertex{VertPos(-0.5f,  0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(0.0f, 0.0f, -1.0f),Color(white)},
			Vertex{VertPos(-0.5f, -0.5f, -0.5f), TexCoords(0.0f, 0.0f), Normals(0.0f, 0.0f, -1.0f),Color(white)}, //
    	
			Vertex{VertPos(-0.5f, -0.5f,  0.5f), TexCoords(0.0f, 0.0f), Normals(0.0f, 0.0f, 1.0f),Color(white)},
			Vertex{VertPos( 0.5f, -0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(0.0f, 0.0f, 1.0f),Color(red)},
			Vertex{VertPos( 0.5f,  0.5f,  0.5f), TexCoords(1.0f, 1.0f), Normals(0.0f, 0.0f, 1.0f),Color(green)},
			Vertex{VertPos( 0.5f,  0.5f,  0.5f), TexCoords(1.0f, 1.0f), Normals(0.0f, 0.0f, 1.0f),Color(blue)},
			Vertex{VertPos(-0.5f,  0.5f,  0.5f), TexCoords(0.0f, 1.0f), Normals(0.0f, 0.0f, 1.0f),Color(white)},
			Vertex{VertPos(-0.5f, -0.5f,  0.5f), TexCoords(0.0f, 0.0f), Normals(0.0f, 0.0f, 1.0f),Color(white)}, //
    	
			Vertex{VertPos(-0.5f,  0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(-1.0f, 0.0f, 0.0f),Color(white)},
			Vertex{VertPos(-0.5f,  0.5f, -0.5f), TexCoords(1.0f, 1.0f), Normals(-1.0f, 0.0f, 0.0f),Color(red)},
			Vertex{VertPos(-0.5f, -0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(-1.0f, 0.0f, 0.0f),Color(green)},
			Vertex{VertPos(-0.5f, -0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(-1.0f, 0.0f, 0.0f),Color(blue)},
			Vertex{VertPos(-0.5f, -0.5f,  0.5f), TexCoords(0.0f, 0.0f), Normals(-1.0f, 0.0f, 0.0f),Color(white)},
			Vertex{VertPos(-0.5f,  0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(-1.0f, 0.0f, 0.0f),Color(white)}, //
    	
			Vertex{VertPos( 0.5f,  0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(1.0f, 0.0f, 0.0f),Color(white)},
			Vertex{VertPos( 0.5f,  0.5f, -0.5f), TexCoords(1.0f, 1.0f), Normals(1.0f, 0.0f, 0.0f),Color(red)},
			Vertex{VertPos( 0.5f, -0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(1.0f, 0.0f, 0.0f),Color(green)},
			Vertex{VertPos( 0.5f, -0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(1.0f, 0.0f, 0.0f),Color(blue)},
			Vertex{VertPos( 0.5f, -0.5f,  0.5f), TexCoords(0.0f, 0.0f), Normals(1.0f, 0.0f, 0.0f),Color(white)},
			Vertex{VertPos( 0.5f,  0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(1.0f, 0.0f, 0.0f),Color(white)}, //
    	
			Vertex{VertPos(-0.5f, -0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(0.0f, -1.0f, 0.0f),Color(white)},
			Vertex{VertPos( 0.5f, -0.5f, -0.5f), TexCoords(1.0f, 1.0f), Normals(0.0f, -1.0f, 0.0f),Color(red)},
			Vertex{VertPos( 0.5f, -0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(0.0f, -1.0f, 0.0f),Color(green)},
			Vertex{VertPos( 0.5f, -0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(0.0f, -1.0f, 0.0f),Color(blue)},
			Vertex{VertPos(-0.5f, -0.5f,  0.5f), TexCoords(0.0f, 0.0f), Normals(0.0f, -1.0f, 0.0f),Color(white)},
			Vertex{VertPos(-0.5f, -0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(0.0f, -1.0f, 0.0f),Color(white)}, //
    	
			Vertex{VertPos(-0.5f,  0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(0.0f, 1.0f, 0.0f),Color(white)},
			Vertex{VertPos( 0.5f,  0.5f, -0.5f), TexCoords(1.0f, 1.0f), Normals(0.0f, 1.0f, 0.0f),Color(red)},
			Vertex{VertPos( 0.5f,  0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(0.0f, 1.0f, 0.0f),Color(green)},
			Vertex{VertPos( 0.5f,  0.5f,  0.5f), TexCoords(1.0f, 0.0f), Normals(0.0f, 1.0f, 0.0f),Color(blue)},
			Vertex{VertPos(-0.5f,  0.5f,  0.5f), TexCoords(0.0f, 0.0f), Normals(0.0f, 1.0f, 0.0f),Color(white)},
			Vertex{VertPos(-0.5f,  0.5f, -0.5f), TexCoords(0.0f, 1.0f), Normals(0.0f, 1.0f, 0.0f),Color(white)}
    };

    std::vector<unsigned int> indices = std::vector<unsigned int>
    {
        0, 1, 2, // first face
        2, 1, 3 // second face
    };

    // Textures

    //TODO: Make this a parameter later
    unsigned int textureID = 0;
    std::string textureName = "default_64x64_f1.jpg";
    std::string texturePath = std::string(pData->GetTextureFolderPath()) + textureName;

    std::vector<Texture> textures = std::vector
    {
        Texture{textureID, texturePath},
    };
};

#endif // !ENGINE_H