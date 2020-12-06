#include "../../include/opengl/ElementBufferObject.hpp"

#include <iostream>

namespace opengl
{

    ElementBufferObject::ElementBufferObject()
    {
        glGenBuffers(1, &m_index);
    }

    ElementBufferObject::~ElementBufferObject()
    {
        std::cout << "[EBO] Delete EBO with index " << m_index << std::endl;
        glDeleteBuffers(1, &m_index);
    }

    void ElementBufferObject::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    }

    void ElementBufferObject::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

} // namespace opengl