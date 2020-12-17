#pragma once
#ifndef _Model_HPP_
#define _Model_HPP_

#include <engine/Camera.hpp>
#include <engine/Shader.hpp>
#include <engine/VertexArrayObject.hpp>
#include <engine/utils/filesystem.hpp>
#include <engine/dependencies/tiny_gltf.h>

#include <GL/glew.h>

namespace engine
{

    class Model
    {
    private:
        tinygltf::Model m_model;
        fs::path m_gltfFilePath;

        std::vector<GLuint> m_textureObjects;
        std::vector<GLuint> m_bufferObjects;
        std::vector<GLuint> m_vertexArrayObjects;

        std::vector<VertexArrayObject::VaoRange> m_meshToVertexArrays;

        GLuint m_whiteTexture = 0;

        bool m_lightFromCamera;
        bool m_applyOcclusion;

    public:
        Model(const std::string &gltfFilePath);

        bool loadGltfFile(tinygltf::Model &model);

        std::vector<GLuint> createTextureObjects(const tinygltf::Model &model) const;

        std::vector<GLuint> createBufferObjects(const tinygltf::Model &model);

        std::vector<GLuint> createVertexArrayObjects(const tinygltf::Model &model,
                                                     const std::vector<GLuint> &bufferObjects,
                                                     std::vector<VertexArrayObject::VaoRange> &meshToVertexArrays);

        /// \brief Renders the model to the screen/window.
        /// \param camera : A pointer to the camera of the application.
        /// \param shader : The shaders associated to the model.
        /// \param time : The current time of the window manager.
        void render(const Camera *camera, Shader &shader, float time);
    };

} // namespace engine

#endif /* _Model_HPP_ */