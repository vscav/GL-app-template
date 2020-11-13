#pragma once
#ifndef _Sphere_HPP_
#define _Sphere_HPP_

#include "Common.hpp"

#include <glm/gtc/constants.hpp>

#include <cmath>
#include <vector>
#include <iostream>

class Sphere
{
    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

private:
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount;

public:
    Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong) : m_nVertexCount(0)
    {
        build(radius, discLat, discLong);
    }

    const ShapeVertex *getDataPointer() const
    {
        return &m_Vertices[0];
    }

    GLsizei getVertexCount() const
    {
        return m_nVertexCount;
    }
};

#endif /* _Sphere_HPP_ */