#pragma once
#ifndef _TrackballCamera_HPP_
#define _TrackballCamera_HPP_

#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

class TrackballCamera : public Camera
{
private:
    float m_fDistance; // Distance from the center of the scene
    float m_fAngleX;   // Angle made by the camera around the x axis of the scene
    float m_fAngleY;   // angle made by the camera around the y axis of the scene

public:
    TrackballCamera();
    ~TrackballCamera();

    virtual void moveFront(float t) override;
    virtual void rotateLeft(float degrees) override;
    virtual void rotateUp(float degrees) override;

    virtual glm::mat4 getViewMatrix() const override;
    virtual glm::mat4 getProjectionMatrix() const override;
    virtual glm::mat4 getVPMatrix() const override;
};

#endif /* _TrackballCamera_HPP_ */