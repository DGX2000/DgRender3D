#include "mesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Mesh::Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned int> &&indices)
    : vertices(vertices), indices(indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
                 &(this->vertices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int),
                 &(this->indices[0]), GL_STATIC_DRAW);

    // Vertex.position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);

    // Vertex.normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Vertex.texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh::setTexture(Texture *texture)
{
    this->texture = texture;
}

void Mesh::draw(Shader* shader)
{
    shader->use();

    // TODO: Remove after the model class is finished!
    if(texture.has_value())
    {
        glActiveTexture(GL_TEXTURE0);
        texture.value()->bind();
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

Mesh Mesh::createCube()
{
    std::vector<Vertex> vertices
    {
        {{-0.5F, -0.5F, 0.5F}, {-1.0F, -1.0F, 1.0F}, {0.0F, 0.0F}},   // 0 front-face bottom-left
        {{0.5F, -0.5F, 0.5F}, {1.0F, -1.0F, 1.0F}, {1.0F, 0.0F}},   // 1 front-face bottom-right
        {{0.5F, 0.5F, 0.5F}, {1.0F, 1.0F, 1.0F}, {1.0F, 1.0F}},   // 2 front-face top-right
        {{-0.5F, 0.5F, 0.5F}, {-1.0F, 1.0F, 1.0F}, {0.0F, 1.0F}},   // 3 front-face top-left

        {{-0.5F, -0.5F, -0.5F}, {-1.0F, -1.0F, -1.0F}, {0.0F, 0.0F}},   // 4 back-face bottom-left
        {{0.5F, -0.5F, -0.5F}, {1.0F, -1.0F, -1.0F}, {1.0F, 0.0F}},   // 5 back-face bottom-right
        {{0.5F, 0.5F, -0.5F}, {1.0F, 1.0F, -1.0F}, {1.0F, 1.0F}},   // 6 back-face top-right
        {{-0.5F, 0.5F, -0.5F}, {-1.0F, 1.0F, -1.0F}, {0.0F, 1.0F}}    // 7 back-face top-left
    };

    std::vector<unsigned int> indices
    {
        0, 1, 3, 1, 2, 3,   // front
        4, 5, 7, 5, 6, 7,   // back
        0, 1, 4, 1, 5, 4,   // bottom
        1, 5, 2, 5, 6, 2,   // right
        3, 2, 7, 2, 6, 7,   // top
        4, 3, 7, 3, 0, 4    // left
    };

    return Mesh(std::move(vertices), std::move(indices));
}
