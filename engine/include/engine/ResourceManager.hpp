#pragma once
#ifndef _ResourceManager_HPP_
#define _ResourceManager_HPP_

#include <engine/Texture.hpp>
#include <engine/Container.hpp>
#include <engine/FilePath.hpp>

#include <GL/glew.h>

#include <unordered_map>
#include <vector>
#include <memory>

namespace engine
{

    class ResourceManager
    {
    private:
        /// \brief Default constructor.
        ResourceManager() = default;
        /// \brief Default destructor.
        ~ResourceManager() = default;

    public:
        static ResourceManager &getInstance()
        {
            static ResourceManager instance;

            return instance;
        }

        /// \brief Copy constructor.
        ResourceManager(ResourceManager const &) = delete;
        /// \brief Affectation operator.
        ResourceManager &operator=(ResourceManager const &) = delete;

        // Loads an image (if not cached) and generates an OpenGL texture
        GLuint loadTexture(const std::string &path);

        GLuint loadCubeMapTexture(Container<std::string> &faces);
    };

} // namespace engine

#endif /* _ResourceManager_HPP_ */