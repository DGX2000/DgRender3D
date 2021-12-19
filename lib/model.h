#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "mesh.h"
#include "transformnode.h"
#include "meshnode.h"

class Model
{
public:
    Model(const std::string& filename);

    SceneNode* getRootNode();

private:
    const class aiScene* loadScene(const std::string& filename) const;
    void transformSceneToSceneTree(TransformNode* currentNode, class aiNode* currentSceneNode, const class aiScene* scenes);

    Mesh processMesh(const class aiMesh* mesh, const class aiScene* scene) const;

private:
    std::unique_ptr<TransformNode> rootNode;

    std::unordered_map<std::string, Mesh> meshes;
    std::unordered_map<std::size_t, TransformNode> transformNodes;
    std::unordered_map<std::string, MeshNode> meshNodes;
};

#endif // MODEL_H
