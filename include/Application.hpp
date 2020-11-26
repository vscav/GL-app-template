#pragma once
#ifndef _Application_HPP_
#define _Application_HPP_

#include "GLApplication.hpp"
#include "Shader.hpp"
#include "FreeflyCamera.hpp"
#include "Sphere.hpp"
#include "Program.hpp"

#include "./dependencies/glm.hpp"

#include <GLFW/glfw3.h>

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

#endif /* _Application_HPP_ */
