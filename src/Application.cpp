#include "../include/GLError.hpp"
#include "../include/Sphere.hpp"

#include "../include/Application.hpp"

#include <functional>

Application::Application()
    : GLApplication(),
      m_sphere(1, 64, 32),
      m_sphereShader("../shader/3D.vert", "../shader/directionallight.frag")
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : GLApplication(title, width, height, fullScreen),
      m_sphere(1, 64, 32),
      m_sphereShader("../shader/3D.vert", "../shader/directionallight.frag")
{
}

Application::~Application()
{
}

void Application::loop()
{
  // Print fps in console by passing true
  TimeManager::getInstance().calculateFrameRate(false);

  // Get current context time
  float t = getTime();

  // How to use window utils class (wireframe example) :
  // getWindowManager()->getWindowUtils()->goWireframe(true);

  // Render Sphere
  m_sphere.render(getCamera(), m_sphereShader, t);

  // Check for GL errors
  // glCheckError(__FILE__, __LINE__);
}
