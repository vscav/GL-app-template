#pragma once

#include "../utils/Image.hpp"
#include "../iterator/Container.hpp"

#include <GL/glew.h>

#include <vector>
#include <string>

namespace opengl
{

    class Texture
    {
    public:
        static GLuint loadTexture(std::string path);

        static GLuint loadCubeMapTexture(iterator::Container<std::string> faces);
    };

} // namespace opengl
