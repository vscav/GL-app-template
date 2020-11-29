#include "../../include/opengl/VertexArrayObject.hpp"

#include <iostream>

namespace opengl
{

    VertexArrayObject::VertexArrayObject()
    {
        glGenVertexArrays(1, &m_index);
    }

    VertexArrayObject::~VertexArrayObject()
    {
        std::cout << "[VAO] Delete VAO with index " << m_index << std::endl;
        glDeleteVertexArrays(1, &m_index);
    }

    void VertexArrayObject::bind()
    {
        glBindVertexArray(m_index);
    }

    void VertexArrayObject::unbind()
    {
        glBindVertexArray(0);
    }

} // namespace opengl