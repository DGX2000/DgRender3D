#include "meshnode.h"

#include "mesh.h"
#include "shader.h"

MeshNode::MeshNode(Mesh* mesh, Shader* shader)
    : mesh(mesh), shader(shader)
{

}

void MeshNode::draw(const glm::mat4& worldToCamera, const glm::mat4& modelToWorld) const
{
    shader->setUniform("camera", worldToCamera);
    shader->setUniform("model", modelToWorld);
    mesh->draw(shader);
}

void MeshNode::transform(glm::mat4& transformation) const
{

}

bool MeshNode::isDrawable() const
{
    return true;
}
