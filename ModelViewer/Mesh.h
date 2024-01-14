#ifndef MESH_H
#define MESH_H

#include <vector>

#include "ErrorHandler.h"
#include "CustomStructs.h"
#include "IObject.h"

class Mesh : public IObject
{
public:
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures = {}, std::unique_ptr<Transform> transform = nullptr)
    : vertices(TranslateVertices(vertices, transform)), indices(indices), pTransform(std::move(transform)), pVertexBufferObject(new unsigned int(EMPTY)), pElementBufferObject(new unsigned int(EMPTY)) { }
    
private:
    // Bytes
    constexpr int GetPositionSize() const { return sizeof(glm::vec3); }
    constexpr int GetColorSize() const { return sizeof(glm::vec4); }
    constexpr int GetTextureSize() const { return sizeof(glm::vec2); }
    constexpr int GetNormalSize() const { return sizeof(glm::vec3); }

    // Numbers
    // Using static_cast to suppress narrowing conversion warning
    constexpr int GetPositionNumber() const { return static_cast<int>(GetPositionSize()) / sizeof(float); }
    constexpr int GetColorNumber() const { return static_cast<int>(GetColorSize()) / sizeof(float); }
    constexpr int GetTextureNumber() const { return static_cast<int>(GetTextureSize()) / sizeof(float); }
    constexpr int GetNormalNumber() const { return static_cast<int>(GetNormalSize()) / sizeof(float); }

    static std::vector<Vertex> TranslateVertices(std::vector<Vertex> vertices, const std::unique_ptr<Transform>& transform);
    
public:
    Transform GetTransform() const { return *pTransform; }

    int LoadTextures();
    void InitializeVertices() const;
    int InitializeTextures();
    void InitializeBuffers() const;
    int Initialize() override;
    void Finalize() override;
    int Update() override;
    int Draw() override;

private:
    const int EMPTY = 0;
    const int BORDER = 0;
    const int MIP_LEVEL = 0;
    const int BUFFER_SIZE = 1;
    const int TEXTURE_COUNT = 1;
    const int DEFAULT_CHANNELS = 0;
    const int VERTEX_ATTRIBUTE_INDEX = 0;
    const int COLOR_ATTRIBUTE_INDEX = 1;
    const int TEXTURE_ATTRIBUTE_INDEX = 2;
    const int NORMAL_ATTRIBUTE_INDEX = 3;
    
    std::vector<Vertex> vertices = {};
    std::vector<unsigned int> indices = {};
    std::vector<Texture> textures = {};

    std::unique_ptr<Transform> pTransform;
    
    std::unique_ptr<unsigned int> pVertexBufferObject;
    std::unique_ptr<unsigned int> pElementBufferObject;
    
    ErrorType errorType = ErrorType::SUCCESS;
};

#endif // !MESH_H