#pragma once
#ifndef _Common_HPP_
#define _Common_HPP_

#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

namespace engine
{

    /// \struct ShapeVertex
    /// \brief Structure used to represent a type of vertice.
    struct ShapeVertex
    {
        glm::vec3 position;  /*!< Position of the vertice. */
        glm::vec3 normal;    /*!< Normal of the vertice. */
        glm::vec2 texCoords; /*!< Texture coordinates of the vertice. */
    };

} // namespace engine

#endif /* _Common_HPP_ */