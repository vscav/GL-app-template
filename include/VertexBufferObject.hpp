#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

class VertexBufferObject
{

private:
    GLuint m_index;

public:
    VertexBufferObject();
    ~VertexBufferObject();

    void bind();
    void unbind();

    template <typename T>
    void setData(const std::vector<T> &data, const GLenum &drawType)
    {
        bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), drawType);
        unbind();
    }

    static void setVertexAttrib(const GLuint &VertexBufferObjectID, const GLuint &size, GLenum dataType, const GLuint &stride, const GLuint &offset);

    inline GLuint getId() const { return m_index; }
};