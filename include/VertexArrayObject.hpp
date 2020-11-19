#pragma once
#ifndef _VertexArrayObject_HPP_
#define _VertexArrayObject_HPP_

#include <GL/glew.h>
#include <glm/glm.hpp>

class VertexArrayObject
{

private:
    GLuint m_index;

public:
    VertexArrayObject();
    ~VertexArrayObject();

    void bind();
    void unbind();

    inline GLuint getId() const { return m_index; }
};

#endif /* _VertexArrayObject_HPP_ */