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
        static GLuint loadTexture(std::string path);

        static GLuint loadCubeMapTexture(Container<std::string> faces);
    };

} // namespace engine
