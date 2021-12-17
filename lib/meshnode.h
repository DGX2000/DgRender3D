#ifndef MESHNODE_H
#define MESHNODE_H

#include "scenenode.h"

class MeshNode : public SceneNode
{
public:
    MeshNode(class Mesh* mesh, class Shader* shader);

protected:
    virtual void draw(const glm::mat4& worldToCamera, const glm::mat4& transformation) const;
    virtual void transform(glm::mat4& initialTransformation) const;
    virtual bool isDrawable() const;

private:
    class Mesh* mesh;
    class Shader* shader;
};

#endif // MESHNODE_H
