#include "../../include/opengl/ElementBufferObject.hpp"

namespace opengl
{

    ElementBufferObject::ElementBufferObject()
    {
        glGenBuffers(1, &m_index);
    }

    ElementBufferObject::~ElementBufferObject()
    {
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

    void ElementBufferObject::setData(const iterator::Container<glm::uvec3> &indices, const GLenum &drawType)
    {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::uvec3) * indices.size(), indices.data(), drawType);
        unbind();
    }

} // namespace opengl