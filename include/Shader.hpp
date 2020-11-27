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

/// \class Shader
/// \brief A class to represent, compile, attach and access the shaders of the application.
class Shader
{
private:
    GLuint m_programId;  /*!< The program ID of the shaders. */
    GLuint m_vertexId;   /*!< The ID of the vertex shader. */
    GLuint m_fragmentId; /*!< The ID of the fragment shader. */
    GLuint m_geometryId; /*!< The ID of the geometric shader. */

    std::unordered_map<std::string, GLint> m_uniformLocationCache; /*!< An unordered map to store the uniforms location. */

    bool m_compiled; /*!< A boolean to indicate the compilation state (success or not). */

    /// \brief Create and compile a shader object.
    /// \param shaderType : The type of the shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER).
    /// \param shaderStr : The path to the shader file.
    GLuint compileShader(const GLenum &shaderType, const std::string &shaderStr);
    /// \brief Read the shader file and return its content as a string.
    /// \param filePath : The path to the shader file.
    std::string parseFile(const char *filepath);
    /// \brief Return a string representing the actual OpenGL shadertype.
    /// \param shaderType : OpenGL shader type (e.g. GL_FRAGMENT_SHADER).
    std::string shaderTypeStr(const GLenum &shaderType);
    /// \brief Attach a shader object to a program object.
    /// \param shaderName : The type of the shader ("vertex", "fragment" or "geometry").
    /// \param id : The ID of the shader.
    void AttachShaderId(const char *shaderName, const GLuint id);

public:
    /// \brief Constructor.
    Shader() = default;
    /// \brief Copy constructor.
    Shader(const Shader &s);
    /// \brief Parameterized Constructor.
    /// \param vertexShader : The path to the vertex shader.
    /// \param fragmentShader : The path to the fragment shader.
    /// \param geometryShader : The path to the geometry shader.
    /// \param fromFile : A boolean to indicate if the shaders are from specific files.
    Shader(const char *vertexShader, const char *fragmentShader, const char *geometryShader = nullptr, const bool &fromFile = true);
    ~Shader();

    /// \brief Install the program object as part of the current rendering state.
    bool bind() const;
    /// \brief Uninstall the program object from the current rendering state.
    inline void unbind() const { glUseProgram(-1); }

    /// \brief Return the location of a uniform variable.
    GLint getUniform(const std::string &uniformName);

    /// \brief  Specify the value of an integer uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param v : The integer value to pass.
    void setInt(const std::string &uniformName, int v);
    /// \brief  Specify the value of a float uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param v : The float value to pass.
    void setFloat(const std::string &uniformName, float v);
    /// \brief  Specify the 2 floats vector uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param v : The vector of 2 floats to pass.
    void setVec2f(const std::string &uniformName, const glm::vec2 &v);
    /// \brief  Specify the 2 floats vector uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param x : The first value of the floats vector.
    /// \param y : The second value of the floats vector.
    void setVec2f(const std::string &uniformName, const float &x, const float &y);
    /// \brief  Specify the 3 floats vector uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param v : The vector of 3 floats to pass.
    void setVec3f(const std::string &uniformName, const glm::vec3 &v);
    /// \brief  Specify the 3 floats vector uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param x : The first value of the floats vector.
    /// \param y : The second value of the floats vector.
    /// \param z : The third value of the floats vector.
    void setVec3f(const std::string &uniformName, const float &x, const float &y, const float &z);
    /// \brief  Specify the 4 floats vector uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param v : The vector of 4 floats to pass.
    void setVec4f(const std::string &uniformName, const glm::vec4 &v);
    /// \brief  Specify the 4 floats vector uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param a : The first value of the floats vector.
    /// \param b : The second value of the floats vector.
    /// \param c : The third value of the floats vector.
    /// \param d : The fourth value of the floats vector.
    void setVec4f(const std::string &uniformName, const float &a, const float &b, const float &c, const float &d);
    /// \brief  Specify the 3x3 floats matrix uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param mat : The value of the 3x3 floats matrix.
    void setMat3(const std::string &uniformName, const glm::mat3 &mat);
    /// \brief  Specify the 4x4 floats matrix uniform variable for the current program object.
    /// \param uniformName : The name of the uniform.
    /// \param mat : The value of the 4x4 floats matrix.
    void setMat4(const std::string &uniformName, const glm::mat4 &mat);

    /// \brief Return the ID of the current program object.
    inline GLuint getID() const { return m_programId; };
};

#endif /* _Shader_HPP_ */