#include "../include/VertexBufferObject.hpp"

VertexBufferObject::VertexBufferObject()
{
    glGenBuffers(1, &m_index);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &m_index);
}

void VertexBufferObject::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
}

void VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::setVertexAttrib(const GLuint &VertexBufferObjectID, const GLuint &size, GLenum dataType, const GLuint &stride, const GLuint &offset)
{
    glEnableVertexAttribArray(VertexBufferObjectID);
    glVertexAttribPointer(
        VertexBufferObjectID,
        size,
        dataType,
        GL_FALSE,
        stride,
        (const GLvoid *)(offset)
    );
}