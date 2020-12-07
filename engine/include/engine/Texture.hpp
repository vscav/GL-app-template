#pragma once

#include <engine/Image.hpp>
#include <engine/Container.hpp>

#include <GL/glew.h>

#include <vector>
#include <string>

namespace engine
{

    class Texture
    {
    public:
        /// \brief Loads a texture.
        /// \return The ID of the texture loaded.
        static GLuint loadTexture(std::string &path);
        /// \brief Loads a cube map texture.
        /// \return The ID of the cube map texture loaded.
        static GLuint loadCubeMapTexture(Container<std::string> faces);
    };

} // namespace engine
