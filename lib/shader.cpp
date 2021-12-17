#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename)
{
    auto vertexShader = fileToString(vertexShaderFilename);
    auto fragmentShader = fileToString(fragmentShaderFilename);

    // After creating the shader program, these l-values are not referenced anymore.
    // Therefore, there is no problem when vertexShader/fragmentShader are destructed at the end of
    // this scope.
    const char* vertexShaderCStr = vertexShader.c_str();
    const char* fragmentShaderCStr = fragmentShader.c_str();


    // TODO: Put these vertex/fragment into small structs with destructor
    unsigned int vertexId, fragmentId;
    int returnValueSuccess;
    char compilationInfo[512];

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexShaderCStr, NULL);
    glCompileShader(vertexId);

    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &returnValueSuccess);
    if(!returnValueSuccess)
    {
        glGetShaderInfoLog(vertexId, 512, NULL, compilationInfo);
        std::cout << compilationInfo << std::endl;
    }


    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentShaderCStr, NULL);
    glCompileShader(fragmentId);

    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &returnValueSuccess);
    if(!returnValueSuccess)
    {
        glGetShaderInfoLog(fragmentId, 512, NULL, compilationInfo);
        std::cout << compilationInfo << std::endl;
    }


    id = glCreateProgram();
    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &returnValueSuccess);
    if(!returnValueSuccess)
    {
        glGetProgramInfoLog(id, 512, NULL, compilationInfo);
        std::cout << compilationInfo << std::endl;
    }


    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void Shader::use() const
{
    glUseProgram(id);
}

void Shader::setUniform(const std::string &name, bool value) const
{
    glProgramUniform1i(id, glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Shader::setUniform(const std::string &name, int value) const
{
    glProgramUniform1i(id, glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setUniform(const std::string &name, float value) const
{
    glProgramUniform1f(id, glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setUniform(const std::string &name, const glm::vec3 &vector) const
{
    glProgramUniform3fv(id, glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(vector));
}

void Shader::setUniform(const std::string &name, const glm::mat4 &matrix) const
{
    glProgramUniformMatrix4fv(id, glGetUniformLocation(id, name.c_str()), 1, false, glm::value_ptr(matrix));
}

std::string Shader::fileToString(const std::string &filename)
{
    std::ifstream file(filename);
    std::stringstream fileStream;
    fileStream << file.rdbuf();

    return fileStream.str();
}
