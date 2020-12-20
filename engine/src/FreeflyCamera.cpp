#include <engine/FreeflyCamera.hpp>
#include <engine/GLApplication.hpp>
#include <engine/utils/common.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

namespace engine
{

    FreeflyCamera::FreeflyCamera()
        : m_position(glm::vec3(.0f, .0f, 5.0f)), m_phi(M_PI), m_theta(.0f)
    {
        if (debug)
            std::cout << "[Camera] Freefly camera created" << std::endl;
        computeDirectionVectors();
    }

    void FreeflyCamera::computeDirectionVectors()
    {
        m_frontVector = glm::vec3(cos(m_theta) * sin(m_phi), sin(m_theta), cos(m_theta) * cos(m_phi));
        m_leftVector = glm::vec3(sin(m_phi + (M_PI / 2)), 0, cos(m_phi + (M_PI / 2)));
        m_upVector = glm::cross(m_frontVector, m_leftVector);
    }

    void FreeflyCamera::moveLeft(const float t)
    {
        m_position += t * m_leftVector * m_speed;
        computeDirectionVectors();
    }

    void FreeflyCamera::moveFront(const float t)
    {
        m_position += t * m_frontVector * m_speed;
        computeDirectionVectors();
    }

    void FreeflyCamera::rotateLeft(const float degrees)
    {
        m_phi += glm::radians(degrees) * m_sensitivity;

        computeDirectionVectors();
    }

    void FreeflyCamera::rotateUp(const float degrees)
    {
        m_theta += glm::radians(degrees) * m_sensitivity;

        computeDirectionVectors();
    }

    glm::mat4 FreeflyCamera::getViewMatrix() const
    {
        glm::mat4 viewMatrix = glm::lookAt(m_position, m_position + m_frontVector, m_upVector);
        return viewMatrix;
    }

    glm::mat4 FreeflyCamera::getProjectionMatrix() const
    {
        auto width = (float)GLApplication::getInstance().getWindowManager()->getWidth();
        auto height = (float)GLApplication::getInstance().getWindowManager()->getHeight();

        return glm::perspective(glm::radians(70.f), width / height, 0.1f, 300.0f);
    }

    glm::mat4 FreeflyCamera::getVPMatrix() const
    {
        return getProjectionMatrix() * getViewMatrix();
    }

} // namespace engine