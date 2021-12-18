#include "texture.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string &filename)
{
    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);

    // this is default behavior, but maybe make it mutable in the future
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, comp;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &comp, 0);
    if(imageData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(imageData);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}
