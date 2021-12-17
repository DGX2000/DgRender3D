#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

    void use() const;

    void setUniform(const std::string& name, bool value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, float value) const;

    void setUniform(const std::string& name, const glm::vec3& vector) const;
    void setUniform(const std::string& name, const glm::mat4& matrix) const;

private:
    static std::string fileToString(const std::string& filename);

private:
    unsigned int id;
};

#endif // SHADER_H
