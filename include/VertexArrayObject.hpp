#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

    class VertexArrayObject {

    private:
        GLuint m_index;

    public:
		VertexArrayObject();
        ~VertexArrayObject();
        
        void bind();
        void unbind();
        
        inline GLuint getId() const { return m_index; }
    };