#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm/glm.hpp>

#include "shader.h"

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

    void draw(Shader* shader);

    static Mesh createCube();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

#endif // MESH_H
