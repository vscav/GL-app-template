#include "../include/GLError.hpp"
#include "../include/Sphere.hpp"

#include "../include/Application.hpp"

#include <functional>
#include <string>

Application::Application()
    : GLApplication(),
      m_sphere(1, 64, 32),
      m_sphereShader("../shader/3D.vert", "../shader/directionallight.frag"),
      m_cubeMap(
          "../res/textures/skybox/front.png",
          "../res/textures/skybox/left.png",
          "../res/textures/skybox/back.png",
          "../res/textures/skybox/bottom.png",
          "../res/textures/skybox/right.png",
          "../res/textures/skybox/top.png"),
      m_cubeMapShader("../shader/skybox.vert", "../shader/skybox.frag")
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : GLApplication(title, width, height, fullScreen),
      m_sphere(1, 64, 32),
      m_sphereShader("../shader/3D.vert", "../shader/directionallight.frag"),
      m_cubeMap(
          "../res/textures/skybox/front.png",
          "../res/textures/skybox/left.png",
          "../res/textures/skybox/back.png",
          "../res/textures/skybox/bottom.png",
          "../res/textures/skybox/right.png",
          "../res/textures/skybox/top.png"),
      m_cubeMapShader("../shader/skybox.vert", "../shader/skybox.frag")
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

  // Render cube map
  getWindowManager()->getWindowUtils()->enableDepthTesting(false);
  m_cubeMap.render(getCamera(), m_cubeMapShader, t);
  getWindowManager()->getWindowUtils()->enableDepthTesting(true);

  // Render Sphere
  m_sphere.render(getCamera(), m_sphereShader, t);

  // Check for GL errors
  // glCheckError(__FILE__, __LINE__);
}
