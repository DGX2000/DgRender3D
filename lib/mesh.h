#ifndef MESH_H
#define MESH_H

#include <optional>
#include <vector>

#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"

class Mesh
{
public:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

public:
    Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices);
    ~Mesh();

    void setTexture(Texture* texture);

    void draw(Shader* shader);

    static Mesh createCube();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // TODO: Add way to have several textures
    std::optional<Texture*> texture;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

#endif // MESH_H
