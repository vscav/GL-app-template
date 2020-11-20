#include "../include/Application.hpp"
#include "../include/GLError.hpp"
#include "../include/Sphere.hpp"

#include <iostream>

Application::Application()
    : GLApplication(),
      m_sphere(new Sphere(1, 64, 32)),
      m_sphereShader("../shader/3D.vert", "../shader/pointlight.frag")
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : GLApplication(title, width, height, fullScreen),
      m_sphere(new Sphere(1, 64, 32)),
      m_sphereShader("../shader/3D.vert", "../shader/pointlight.frag")
{
}

void Application::loop()
{
  // Print fps in console by passing true
  TimeManager::Instance().calculateFrameRate(false);

  // Get current context time
  float t = getTime();

  // Clear GL window
  getWindowManager()->clear();

  // Render Sphere
  m_sphere->render(getCamera(), m_sphereShader, t);

  // Check for GL errors
  // glCheckError(__FILE__, __LINE__);
}
