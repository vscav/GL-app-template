#pragma once
#ifndef _FreeflyCamera_HPP_
#define _FreeflyCamera_HPP_

#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include <cmath>

class FreeflyCamera : public Camera
{
private:
    glm::vec3 m_Position; // Camera position

    // Front vector spherical coordinates
    float m_fPhi;
    float m_fTheta;

    glm::vec3 m_FrontVector; // Front vector
    glm::vec3 m_LeftVector;  // Left vector
    glm::vec3 m_UpVector;    // Up vector

    float m_speed = 5.0;

    // Calcul of Front, Left and Up vectors
    void computeDirectionVectors();

public:
    FreeflyCamera();
    ~FreeflyCamera();

    void moveLeft(float t);
    virtual void moveFront(float t) override;

    virtual void rotateLeft(float degrees) override;
    virtual void rotateUp(float degrees) override;

    virtual inline void setSpeed(const double speed) { m_speed = speed; };
	virtual inline double const getSpeed() const { return m_speed; };

    virtual glm::mat4 getViewMatrix() const override;
    virtual glm::mat4 getProjectionMatrix() const override;
    virtual glm::mat4 getVPMatrix() const override;
};

#endif /* _FreeflyCamera_HPP_ */