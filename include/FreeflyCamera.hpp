#ifndef _FreeflyCamera_HPP_
#define _FreeflyCamera_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include <cmath>

class FreeflyCamera
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
    void moveFront(float t);

    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    inline void setSpeed(const double speed) { m_speed = speed; }
	inline double const getSpeed() const { return m_speed; }

    glm::mat4 getViewMatrix() const;
};

#endif /* _FreeflyCamera_HPP_ */