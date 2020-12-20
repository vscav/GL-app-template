#include <engine/TrackballCamera.hpp>
#include <engine/GLApplication.hpp>
#include <engine/utils/common.hpp>

#include <iostream>

namespace engine
{

    TrackballCamera::TrackballCamera()
        : m_distance(-cameraDistanceToPlayer), m_angleX(0.0f), m_angleY(0.0f), m_zoom(-cameraDistanceToPlayer)
    {
        if (debug)
            std::cout << "[Camera] Trackball camera created" << std::endl;
    }

    void TrackballCamera::moveFront(const float delta)
    {
        m_zoom += m_speed * delta;

        if (m_zoom > maximumDistance)
            m_zoom = maximumDistance;
        else if (m_zoom < minimumDistance)
            m_zoom = minimumDistance;

        m_distance = glm::mix(m_distance, m_zoom, 1 / 8.0f);
    }

    void TrackballCamera::moveLeft(const float t)
    {
    }

    void TrackballCamera::rotateLeft(const float degrees)
    {
        m_angleY += degrees * m_sensitivity;
    }

    void TrackballCamera::rotateUp(const float degrees)
    {
        m_angleX += degrees * m_sensitivity;
    }

    glm::mat4 TrackballCamera::getViewMatrix() const
    {
        glm::mat4 ViewMatrix = glm::mat4(1);
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 0, m_distance));
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_angleX), glm::vec3(1, 0, 0));
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_angleY), glm::vec3(0, 1, 0));

        return ViewMatrix;
    }

    glm::mat4 TrackballCamera::getProjectionMatrix() const
    {
        auto width = (float)GLApplication::getInstance().getWindowManager()->getWidth();
        auto height = (float)GLApplication::getInstance().getWindowManager()->getHeight();

        return glm::perspective(glm::radians(70.f), width / height, 0.1f, 300.0f);
    }

    glm::mat4 TrackballCamera::getVPMatrix() const
    {
        return getProjectionMatrix() * getViewMatrix();
    }

    // void TrackballCamera::update()
    // {
    //     m_distance = glm::mix(m_distance, m_zoom, 1 / 8.0f);
    // }

} // namespace engine