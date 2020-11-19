#include "../include/VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_index);
}

VertexArrayObject::~VertexArrayObject()
{
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