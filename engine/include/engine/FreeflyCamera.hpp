#pragma once
#ifndef _FreeflyCamera_HPP_
#define _FreeflyCamera_HPP_

#include <engine/Camera.hpp>
#include <engine/dependencies/glm.hpp>

#include <cmath>

namespace engine
{

    /// \class FreeflyCamera
    /// \brief Class for creating a freefly camera object, which is an implementation of the abstract base class Camera.
    class FreeflyCamera final : public Camera
    {
    private:
        glm::vec3 m_Position; /*!< The position of the camera. */

        float m_fPhi;   /*!< Front vector Phi spherical coordinates. */
        float m_fTheta; /*!< Front vector Theta spherical coordinates. */

        glm::vec3 m_FrontVector; /*!< The front vector. */
        glm::vec3 m_LeftVector;  /*!< The left vector. */
        glm::vec3 m_UpVector;    /*!< The up vector. */

        float m_speed = 0.15;

        /// \brief Calculates the front, left and up vectors of the camera.
        void computeDirectionVectors();

    public:
        /// \brief Constructor.
        FreeflyCamera();
        /// \brief Destructor.
        ~FreeflyCamera() override = default;

        /// \brief Moves the camera forward or backward according to a certain value.
        /// \param t : The value used to move the camera forward or back.
        void moveFront(float t) override;
        /// \brief Moves the camera to the right or to the left according to the t value.
        /// \param t : The value used to move the camera on the right or on the left.
        void moveLeft(float t) override;

        /// \brief Rotates the camera to the right or to the left according to the degree value.
        /// \param degrees : The value (in degrees) used to move the camera on the right or on the left.
        void rotateLeft(float degrees) override;
        /// \brief Rotates the camera to the top or the bottom according to the degree value.
        /// \param degrees : The value (in degrees) used to move the camera to the top or to the bottom.
        void rotateUp(float degrees) override;

        /// \brief Sets the camera speed value.
        /// \param speed : The value representing the speed apply to the camera.
        inline void setSpeed(const float speed) override { m_speed = speed; };
        /// \brief Gets the camera speed value.
        /// \return The current speed of the camera.
        inline float getSpeed() const override { return m_speed; };

        /// \brief Calculates and get the view matrix of the camera based on its member variables.
        /// \return The view matrix of the camera.
        glm::mat4 getViewMatrix() const override;
        /// \brief Calculates and get the projection matrix of the camera based on its member variables.
        /// \return The projection matrix of the camera.
        glm::mat4 getProjectionMatrix() const override;
        /// \brief Calculates and get the view projection matrix of the camera based on the view and the projection matrices.
        /// \return The view projection matrix of the camera.
        glm::mat4 getVPMatrix() const override;

        /// \brief Gets the current position of the camera.
        /// \return The position of the camera.
        inline const glm::vec3 getPosition() const override { return m_Position; };
    };

} // namespace engine

#endif /* _FreeflyCamera_HPP_ */