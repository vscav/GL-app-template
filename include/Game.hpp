#pragma once
#ifndef _Game_HPP_
#define _Game_HPP_

#include "GLApplication.hpp"
#include "Shader.hpp"
#include "Shader2.hpp"
#include "FreeflyCamera.hpp"
#include "Sphere.hpp"
#include "Program.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Game : public GLApplication
{
private:
  float m_time = 0.f;
  const int m_size = 100;

  Sphere *m_sphere;

  Shader2 m_sphereShader;

protected:
  virtual void loop();

public:
  Game();
};

#endif /* _Game_HPP_ */
