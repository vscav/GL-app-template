#pragma once
#ifndef _FreeflyCamera_HPP_
#define _FreeflyCamera_HPP_

#include "Camera.hpp"

#include "./dependencies/glm.hpp"

#include <cmath>

/// \class FreeflyCamera
/// \brief Class for creating a freefly camera object, which is an implementation of the abstract base class Camera.
class FreeflyCamera : public Camera
{
private:
    glm::vec3 m_Position; /*!< The position of the camera. */

    float m_fPhi;   /*!< Front vector Phi spherical coordinates. */
    float m_fTheta; /*!< Front vector Theta spherical coordinates. */

    glm::vec3 m_FrontVector; /*!< The front vector. */
    glm::vec3 m_LeftVector;  /*!< The left vector. */
    glm::vec3 m_UpVector;    /*!< The up vector. */

    float m_speed = 5.0;

    /// \brief Calcul the Front, Left and Up vectors.
    void computeDirectionVectors();

public:
    /// \brief Constructor.
    FreeflyCamera();
    /// \brief Destructor.
    ~FreeflyCamera();

    /// \brief Move the camera forward or backward according to a certain value.
    /// \param t : The value used to move the camera forward or back.
    virtual void moveFront(float t) override;
    /// \brief Move the camera to the right or to the left according to the t value.
    /// \param t : The value used to move the camera on the right or on the left.
    virtual void moveLeft(float t) override;

    /// \brief Rotate the camera to the right or to the left according to the degree value.
    /// \param degrees : The value (in degrees) used to move the camera on the right or on the left.
    virtual void rotateLeft(float degrees) override;
    /// \brief Rotate the camera to the top or the bottom according to the degree value.
    /// \param degrees : The value (in degrees) used to move the camera to the top or to the bottom.
    virtual void rotateUp(float degrees) override;

    /// \brief Set the camera speed value.
    /// \param speed : The value representing the speed apply to the camera.
    virtual inline void setSpeed(const double speed) { m_speed = speed; };
    /// \brief Get the camera speed value.
    /// \param speed : The value representing the speed apply to the camera.
    virtual inline double const getSpeed() const { return m_speed; };

    /// \brief Calculate and get the view matrix of the camera based on its member variables.
    virtual glm::mat4 getViewMatrix() const override;
    /// \brief Calculate and get the projection matrix of the camera based on its member variables.
    virtual glm::mat4 getProjectionMatrix() const override;
    /// \brief Calculate and get the view projection matrix of the camera based on the view and the projection matrices.
    virtual glm::mat4 getVPMatrix() const override;

    /// \brief Get the current position of the camera.
    virtual inline const glm::vec3 getPosition() const { return m_Position; };
};

#endif /* _FreeflyCamera_HPP_ */