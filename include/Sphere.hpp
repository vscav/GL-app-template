#pragma once
#ifndef _Sphere_HPP_
#define _Sphere_HPP_

#include "Common.hpp"
#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "./dependencies/glm.hpp"

#include <cmath>
#include <vector>
#include <iostream>

class Sphere
{
    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

private:
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount;

    VertexArrayObject m_vao;
    VertexBufferObject m_vbo;

    void buildVAO();

    void buildVBO();

public:
    Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong);
    ~Sphere();

    inline const ShapeVertex *getDataPointer() const { return &m_Vertices[0]; };

    inline std::vector<ShapeVertex> getVertices() const { return m_Vertices; };

    inline GLsizei getVertexCount() const { return m_nVertexCount; };

    void render(const Camera *camera, Shader &shader, float time);
};

#endif /* _Sphere_HPP_ */