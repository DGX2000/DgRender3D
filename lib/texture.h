#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
    Texture(const std::string& filename);

    void bind() const;

private:
    unsigned int id;
};

#endif // TEXTURE_H
