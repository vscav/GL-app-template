#pragma once
#ifndef _Sphere_HPP_
#define _Sphere_HPP_

#include "Camera.hpp"
#include "../utils/Common.hpp"
#include "../opengl/VertexBufferObject.hpp"
#include "../opengl/VertexArrayObject.hpp"
#include "../opengl/Shader.hpp"
#include "../iterator/Container.hpp"

#include "../dependencies/glm.hpp"

#include <cmath>
#include <vector>
#include <iostream>

namespace world
{

    /// \class Sphere
    /// \brief Class used to represent a sphere.
    class Sphere
    {
        /// \brief Build the sphere mesh.
        /// \param radius : The radius of the sphere.
        /// \param discLat : The number of segments to discretize the latitude of the sphere.
        /// \param discLong : The number of segments to discretize the longitude of the sphere.
        void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

    private:
        iterator::Container<utils::ShapeVertex> m_vertices; /*!< Vertices of the sphere. */
        GLsizei m_nVertexCount;                      /*!< Number of vertices. */

        opengl::VertexArrayObject m_vao;  /*!< Vertex Array Object of the sphere. */
        opengl::VertexBufferObject m_vbo; /*!< Vertex Buffer Object of the sphere. */

        /// \brief Build the Vertex Array Object of the sphere.
        void buildVAO();

        /// \brief Build the Vertex Buffer Object of the sphere.
        void buildVBO();

    public:
        /// \brief Build the Vertex Buffer Object of the sphere.
        /// \param radius : The radius of the sphere.
        /// \param discLat : The number of segments to discretize the latitude of the sphere.
        /// \param discLong : The number of segments to discretize the longitude of the sphere.
        Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong);
        ~Sphere();

        /// \brief Return the data (vertices) of the sphere.
        inline iterator::Container<utils::ShapeVertex> getVertices() const { return m_vertices; };

        /// \brief Return the number of vertices of the sphere.
        inline GLsizei getVertexCount() const { return m_nVertexCount; };

        /// \brief Render the sphere to the screen/window.
        /// \param camera : A pointer to the camera of the application.
        /// \param shader : The shaders associated to the sphere.
        /// \param time : The time of the window manager.
        void render(const Camera *camera, opengl::Shader &shader, float time);
    };

} // namespace world

#endif /* _Sphere_HPP_ */