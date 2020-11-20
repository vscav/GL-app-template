#pragma once
#ifndef _Game_HPP_
#define _Game_HPP_

#include "GLApplication.hpp"
#include "Shader.hpp"
#include "FreeflyCamera.hpp"
#include "Sphere.hpp"
#include "Program.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/type_ptr.hpp>

class Application : public GLApplication
{
private:
  Sphere m_sphere;

  Shader m_sphereShader;

protected:
  virtual void loop();

public:
  Application();
  Application(std::string title, int width, int height, bool fullScreen);
  ~Application();
};

#endif /* _Game_HPP_ */
