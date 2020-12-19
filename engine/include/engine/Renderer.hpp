#pragma once
#ifndef _Renderer_HPP_
#define _Renderer_HPP_

#include <engine/Camera.hpp>
#include <engine/Shader.hpp>
#include <engine/dependencies/glm.hpp>

#include <vector>
#include <memory>

namespace engine
{

    class Renderer
    {
    private:
        Renderer() = default;
        ~Renderer() = default;

        std::shared_ptr<Camera> m_camera;
        glm::mat4 m_projection;
        glm::mat4 m_view;

    public:
        static Renderer &getInstance()
        {
            static Renderer instance;
            return instance;
        }

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        void sendModelMatrixUniforms(const glm::mat4 &modelMatrix, Shader &shader, bool removeTranslationView = false);

        void sendBlinnPhongUniforms(Shader &shader) const;

        inline void updateViewMatrix() { m_view = m_camera->getViewMatrix(); };

        inline void updateProjectionMatrix() { m_projection = m_camera->getProjectionMatrix(); };

        inline void setCamera(std::shared_ptr<Camera> camera) { m_camera = std::move(camera); };
    };

} // namespace engine

#endif /* _Renderer_HPP_ */