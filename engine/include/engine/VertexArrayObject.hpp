#pragma once
#ifndef _VertexArrayObject_HPP_
#define _VertexArrayObject_HPP_

#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

namespace engine
{

    /// \class VertexArrayObject
    /// \brief Class used to represent an OpenGL VAO.
    class VertexArrayObject
    {

    private:
        GLuint m_index; /*!< The index of the VAO. */

    public:
        /// \brief Constructor.
        VertexArrayObject();
        /// \brief Destructor.
        ~VertexArrayObject();

        /// \brief Bind the VAO.
        void bind();
        /// \brief Unbind the VAO.
        void unbind();

        /// \brief Return the id of the VAO instance.
        inline GLuint getId() const { return m_index; }
    };

} // namespace engine

#endif /* _VertexArrayObject_HPP_ */