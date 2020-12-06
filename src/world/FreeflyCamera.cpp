#include "../../include/world/FreeflyCamera.hpp"
#include "../../include/GLApplication.hpp"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

namespace world
{

    FreeflyCamera::FreeflyCamera()
        : m_Position(glm::vec3(.0f, .0f, 3.0f)), m_fPhi(M_PI), m_fTheta(.0f)
    {
        computeDirectionVectors();
    }

    void FreeflyCamera::computeDirectionVectors()
    {
        m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
        m_LeftVector = glm::vec3(sin(m_fPhi + (M_PI / 2)), 0, cos(m_fPhi + (M_PI / 2)));
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }

    void FreeflyCamera::moveLeft(float t)
    {
        m_Position += t * m_LeftVector;
        computeDirectionVectors();
    }

    void FreeflyCamera::moveFront(float t)
    {
        m_Position += t * m_FrontVector;
        computeDirectionVectors();
    }

    void FreeflyCamera::rotateLeft(float degrees)
    {
        m_fPhi += glm::radians(degrees);
        computeDirectionVectors();
    }

    void FreeflyCamera::rotateUp(float degrees)
    {
        m_fTheta += glm::radians(degrees);
        computeDirectionVectors();
    }

    glm::mat4 FreeflyCamera::getViewMatrix() const
    {
        glm::mat4 viewMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
        return viewMatrix;
    }

    glm::mat4 FreeflyCamera::getProjectionMatrix() const
    {
        float width = GLApplication::getInstance().getWindowManager()->getWidth();
        float height = GLApplication::getInstance().getWindowManager()->getHeight();

        return glm::perspective(glm::radians(70.f), width / height, 0.1f, 300.0f);
    }

    glm::mat4 FreeflyCamera::getVPMatrix() const
    {
        return getProjectionMatrix() * getViewMatrix();
    }

} // namespace world