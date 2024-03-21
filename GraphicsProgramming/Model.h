#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>
#include <vector>

#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
    explicit Model(std::string path, const bool gamma = false) : path(std::move(path)), gammaCorrection(gamma),
                                                                 hasTextures(false)
    {
    }

    void Initialize();
    void Draw(const Shader &shader) const;

    [[nodiscard]] bool HasTextures() const { return hasTextures; }

private:
    std::vector<Texture> texturesLoaded;
    std::vector<Mesh> meshes;
    std::string directory;
    std::string path;
    
    bool gammaCorrection;
    bool hasTextures;

    void ProcessNode(const aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(const aiMaterial* material, aiTextureType type, const std::string& typeName);
    static unsigned TextureFromFile(const char* aPath, const std::string& aDirectory, bool gamma);

    MessageType message = MessageType::SUCCESS;
};

#endif // MODEL_ONE_H