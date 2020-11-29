#pragma once
#ifndef _Camera_HPP_
#define _Camera_HPP_

#include "../dependencies/glm.hpp"

namespace world
{

    /// \class Camera
    /// \brief Class for managing the creation of a camera. This class should be inherited from to create
    /// specific implementations (freefly, trackball, etc.).
    class Camera
    {
    public:
        /// \brief Destructor. This is needed so that the class inheriting this will have it's deconstructor called.
        virtual ~Camera() {}

        /// \brief Move the camera forward or backward according to a certain value.
        /// \param t : The value used to move the camera forward or back.
        virtual void moveFront(float t) = 0;
        /// \brief Move the camera to the right or to the left according to the t value.
        /// \param t : The value used to move the camera on the right or on the left.
        virtual void moveLeft(float t) = 0;

        /// \brief Rotate the camera to the right or to the left according to the degree value.
        /// \param degrees : The value (in degrees) used to move the camera on the right or on the left.
        virtual void rotateLeft(float degrees) = 0;
        /// \brief Rotate the camera to the top or the bottom according to the degree value.
        /// \param degrees : The value (in degrees) used to move the camera to the top or to the bottom.
        virtual void rotateUp(float degrees) = 0;

        /// \brief Set the camera speed value.
        /// \param speed : The value representing the speed apply to the camera.
        virtual inline void setSpeed(const double speed) = 0;
        /// \brief Get the camera speed value.
        virtual inline double const getSpeed() const = 0;

        /// \brief Calculate and get the view matrix of the camera based on its member variables.
        virtual glm::mat4 getViewMatrix() const = 0;
        /// \brief Calculate and get the projection matrix of the camera based on its member variables.
        virtual glm::mat4 getProjectionMatrix() const = 0;
        /// \brief Calculate and get the view projection matrix of the camera based on the view and the projection matrices.
        virtual glm::mat4 getVPMatrix() const = 0;

        /// \brief Get the current position of the camera.
        virtual glm::vec3 const getPosition() const = 0;
    };

} // namespace world

#endif /* _Camera_HPP_ */