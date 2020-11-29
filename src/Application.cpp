#include "../include/opengl/GLError.hpp"
// #include "../include/world/Sphere.hpp"

#include "../include/Application.hpp"

#include <functional>
#include <string>

Application::Application()
    : GLApplication(),
      m_sphere(1, 64, 32),
      m_sphereShader("../res/shaders/3D.vert", "../res/shaders/directionallight.frag"),
      m_cubeMap(
          "../res/textures/skybox/space/front.png",
          "../res/textures/skybox/space/left.png",
          "../res/textures/skybox/space/back.png",
          "../res/textures/skybox/space/bottom.png",
          "../res/textures/skybox/space/right.png",
          "../res/textures/skybox/space/top.png"),
      m_cubeMapShader("../res/shaders/skybox.vert", "../res/shaders/skybox.frag")
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : GLApplication(title, width, height, fullScreen),
      m_sphere(1, 64, 32),
      m_sphereShader("../res/shaders/3D.vert", "../res/shaders/directionallight.frag"),
      m_cubeMap(
          "../res/textures/skybox/space/front.png",
          "../res/textures/skybox/space/left.png",
          "../res/textures/skybox/space/back.png",
          "../res/textures/skybox/space/bottom.png",
          "../res/textures/skybox/space/right.png",
          "../res/textures/skybox/space/top.png"),
      m_cubeMapShader("../res/shaders/skybox.vert", "../res/shaders/skybox.frag")
{
}

Application::~Application()
{
}

void Application::loop()
{
  // Print fps in console by passing true
  manager::TimeManager::getInstance().calculateFrameRate(false);

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
  // opengl::glCheckError(__FILE__, __LINE__);
}
