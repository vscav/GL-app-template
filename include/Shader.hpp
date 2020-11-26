#pragma once
#ifndef _Shader_HPP_
#define _Shader_HPP_

#include "./dependencies/glm.hpp"

#include <GL/glew.h>

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Shader
{
private:
    GLuint m_programId;
    GLuint m_vertexId;
    GLuint m_fragmentId;
    GLuint m_geometryId;

    std::unordered_map<std::string, GLint> m_uniformLocationCache;

    bool m_compiled;

    GLuint compileShader(const GLenum &shaderType, const std::string &shaderStr);
    std::string parseFile(const char *filepath);
    std::string shaderTypeStr(const GLenum &shaderType);
    void AttachShaderId(const char *shaderName, const GLuint id);

public:
    Shader() = default;
    Shader(const Shader &s);
    Shader(const char *vertexShader, const char *fragmentShader, const char *geometryShader = nullptr, const bool &fromFile = true);
    ~Shader();

    bool bind() const;
    inline void unbind() const { glUseProgram(-1); }

    GLint getUniform(const std::string &uniformName);

    void setInt(const std::string &uniformName, int v);
    void setFloat(const std::string &uniformName, float v);
    void setVec2f(const std::string &uniformName, const glm::vec2 &v);
    void setVec2f(const std::string &uniformName, const float &x, const float &y);
    void setVec3f(const std::string &uniformName, const glm::vec3 &v);
    void setVec3f(const std::string &uniformName, const float &x, const float &y, const float &z);
    void setVec4f(const std::string &uniformName, const glm::vec4 &v);
    void setVec4f(const std::string &uniformName, const float &a, const float &b, const float &c, const float &d);
    void setMat3(const std::string &uniformName, const glm::mat3 &mat);
    void setMat4(const std::string &uniformName, const glm::mat4 &mat);

    inline GLuint getID() const { return m_programId; };
};

#endif /* _Shader_HPP_ */