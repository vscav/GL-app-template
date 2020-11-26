#pragma once
#ifndef _Camera_HPP_
#define _Camera_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

class Camera
{
public:
    virtual ~Camera() {}

    virtual void moveFront(float t) = 0;
    virtual void moveLeft(float t) = 0;

    virtual void rotateLeft(float degrees) = 0;
    virtual void rotateUp(float degrees) = 0;

    virtual inline void setSpeed(const double speed) = 0;
	virtual inline double const getSpeed() const = 0;

    virtual glm::mat4 getViewMatrix() const = 0;
    virtual glm::mat4 getProjectionMatrix() const = 0;
    virtual glm::mat4 getVPMatrix() const = 0;
};

#endif /* _Camera_HPP_ */