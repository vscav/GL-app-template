#pragma once
#ifndef _CubeMap_HPP_
#define _CubeMap_HPP_

#include <glimac/Image.hpp>

#include "Common.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "./dependencies/glm.hpp"
#include <GL/glew.h>

#include <iostream>
#include <string>

class CubeMap
{
private:
    std::vector<GLfloat> m_vertices; /*!< Vertices of the cube map. */

    std::vector<std::string> m_faces; /*!< A vector containing all the path to each images used to create the cube map texture. */

    GLuint m_cubeMapTexture; /*!< The texture to apply to the cube map */

    VertexArrayObject m_vao;  /*!< Vertex Array Object of the cube map. */
    VertexBufferObject m_vbo; /*!< Vertex Buffer Object of the cube map. */

    /// \brief Build the Vertex Array Object of the cube map.
    void buildVAO();

    /// \brief Build the Vertex Buffer Object of the cube map.
    void buildVBO();

public:
    /// \brief Constructor.
    CubeMap(const char *cubeFront, const char *cubeLeft, const char *cubeBack,
            const char *cubeBottom, const char *cubeRight, const char *cubeTop);
    /// \brief Default destructor.
    ~CubeMap() = default;

    /// \brief Load the approprate image for each side of the cube map.
    GLuint loadCubeMap(std::vector<std::string> faces);

    /// \brief Render the sphere to the screen/window.
    /// \param camera : A pointer to the camera of the application.
    /// \param shader : The shaders associated to the sphere.
    /// \param time : The current time of the window manager.
    void render(const Camera *camera, Shader &shader, float time);

    /// \brief Return the data (vertices) of the cube map.
    inline std::vector<GLfloat> getVertices() const { return m_vertices; };
};

#endif /* _CubeMap_HPP_ */