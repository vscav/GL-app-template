#pragma once
#ifndef _CubeMap_HPP_
#define _CubeMap_HPP_

// #include <glimac/Image.hpp>

#include "../utils/Image.hpp"
#include "Camera.hpp"
#include "../utils/Common.hpp"
#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/VertexBufferObject.hpp"
#include "../opengl/Shader.hpp"
#include "../iterator/Container.hpp"
#include "../iterator/Iterator.hpp"

#include "../dependencies/glm.hpp"
#include <GL/glew.h>

#include <iostream>
#include <string>

namespace world
{

    /// \class CubeMap
    /// \brief Class for creating a cube map, a textured cube
    /// that contains 6 individual 2D textures that each form one side of a cube.
    class CubeMap
    {
    private:
        iterator::Container<GLfloat> m_vertices; /*!< Vertices of the cube map. */

        iterator::Container<std::string> m_faces; /*!< A vector containing all the path to each images used to create the cube map texture. */

        GLuint m_cubeMapTexture; /*!< The texture to apply to the cube map */

        opengl::VertexArrayObject m_vao;  /*!< Vertex Array Object of the cube map. */
        opengl::VertexBufferObject m_vbo; /*!< Vertex Buffer Object of the cube map. */

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
        GLuint loadCubeMap(iterator::Container<std::string> faces);

        /// \brief Render the sphere to the screen/window.
        /// \param camera : A pointer to the camera of the application.
        /// \param shader : The shaders associated to the sphere.
        /// \param time : The current time of the window manager.
        void render(const Camera *camera, opengl::Shader &shader, float time);

        /// \brief Return the data (vertices) of the cube map.
        inline iterator::Container<GLfloat> getVertices() const { return m_vertices; };
    };

} // namespace world

#endif /* _CubeMap_HPP_ */