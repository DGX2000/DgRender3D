#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Model::Model(const std::string &filename)
{
    const aiScene* scene = loadScene(filename);

    if(scene != nullptr)
    {
        transformSceneToSceneTree(rootNode.get(), scene->mRootNode, scene);
    }
}

SceneNode *Model::getRootNode()
{
    return rootNode.get();
}

const aiScene* Model::loadScene(const std::string &filename) const
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(filename, aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_Triangulate);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // TODO: Error handling
        return nullptr;
    }

    return scene;
}

void Model::transformSceneToSceneTree(TransformNode* currentNode, aiNode* currentSceneNode, const aiScene* scene)
{
    transformNodes.insert({transformNodes.size(), TransformNode()});
    TransformNode* addedNode = &(transformNodes.at(transformNodes.size() - 1));
    currentNode->addNode(addedNode);

    for(unsigned int i = 0; i < currentSceneNode->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[currentSceneNode->mMeshes[i]];

        auto processedMesh = processMesh(mesh, scene);
        // TODO: add materials/textures to mesh


        // meshes.insert({mesh->mName, })
    }

    for(unsigned int i = 0; i < currentSceneNode->mNumChildren; ++i)
    {
        transformSceneToSceneTree(currentNode, currentSceneNode->mChildren[i], scene);
    }
}

Mesh Model::processMesh(const aiMesh *mesh, const aiScene *scene) const
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    bool hasTextureCoords = (mesh->mTextureCoords[0] != nullptr);

    vertices.reserve(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Mesh::Vertex vertex;

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if(hasTextureCoords)
        {
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        }

        vertices.emplace_back(vertex);
    }

    indices.reserve(mesh->mNumFaces);
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        auto& face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            indices.emplace_back(face.mIndices[j]);
        }
    }

    return Mesh(std::move(vertices), std::move(indices));
}
