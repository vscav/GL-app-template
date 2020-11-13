#ifndef _Common_HPP_
#define _Common_HPP_

#include <GL/glew.h>
#include <glm/glm.hpp>

struct ShapeVertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

#endif /* _Common_HPP_ */