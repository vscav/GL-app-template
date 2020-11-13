#ifndef _FreeflyCamera_HPP_
#define _FreeflyCamera_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

class Camera
{
public:
    virtual void moveFront(float t) = 0;

    virtual void rotateLeft(float degrees) = 0;
    virtual void rotateUp(float degrees) = 0;

    virtual glm::mat4 getViewMatrix() const = 0;
};

#endif /* _FreeflyCamera_HPP_ */