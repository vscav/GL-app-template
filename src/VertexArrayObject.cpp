#include "../include/VertexArrayObject.hpp"

#include <iostream>

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_index);
}

VertexArrayObject::~VertexArrayObject()
{
    std::cout << "Delete Sphere VAO with index " << &m_index << std::endl;
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