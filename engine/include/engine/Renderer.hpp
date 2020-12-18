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

        void sendModelMatrixUniforms(const glm::mat4 &modelMatrix, Shader &shader, bool removeTranslationView = false)
        {
            updateViewMatrix();
            updateProjectionMatrix();

            if (removeTranslationView)
                m_view = glm::mat4(glm::mat3(m_view));

            shader.bind();

            glm::mat4 MVP = m_projection * m_view * modelMatrix;
            glm::mat4 MV = m_view * modelMatrix;
            glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MV));

            if (!removeTranslationView)
            {
                shader.setMat4("uModelViewMatrix", MV);
                shader.setMat4("uNormalMatrix", NormalMatrix);
            }
            shader.setMat4("uModelViewProjMatrix", MVP);

            shader.unbind();
        }

        void sendBlinnPhongUniforms(Shader &shader) const
        {
            shader.bind();

            glm::mat4 modelLight = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 1, 0));
            glm::vec4 LightDirection = m_view * modelLight * glm::vec4(1, 1, 1, 0);

            shader.setVec3f("uLightDir_vs", LightDirection.x, LightDirection.y, LightDirection.z);
            shader.setVec3f("uLightIntensity", 1.0, 1.0, 1.0);
            shader.setVec3f("uKd", 1.0, 1.0, 1.0);
            shader.setVec3f("uKs", 1.0, 1.0, 1.0);
            shader.setFloat("uShininess", 16.0);

            shader.unbind();
        }

        inline void updateViewMatrix() { m_view = m_camera->getViewMatrix(); };

        inline void updateProjectionMatrix() { m_projection = m_camera->getProjectionMatrix(); };

        inline void setCamera(std::shared_ptr<Camera> camera) { m_camera = std::move(camera); };
    };

} // namespace engine

#endif /* _Renderer_HPP_ */