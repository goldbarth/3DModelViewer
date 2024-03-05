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
    explicit Model(std::string path, const bool gamma = false) : path(std::move(path)), gammaCorrection(gamma)
    {}

    void Initialize();
    void Draw(const Shader &shader) const;
    
    bool HasTextures() const { return hasTextures; }

private:
    std::vector<Texture> texturesLoaded;
    std::vector<Mesh> meshes;
    std::string directory;
    std::string path;
    
    bool gammaCorrection;
    bool hasTextures;

    void ProcessNode(const aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(const aiMaterial* material, aiTextureType type, const std::string& typeName);
    unsigned TextureFromFile(const char* path, const std::string& directory, bool gamma);

    MessageType message = MessageType::SUCCESS;
};

#endif // MODEL_ONE_H