#include <engine/GLError.hpp>

#include "../include/Application.hpp"

#include <functional>
#include <string>

Application::Application()
    : GLApplication(),
      m_sphere(1, 64, 32),
      m_sphereShader("application/res/shaders/3D.vert", "application/res/shaders/directionallight.frag"),
      m_cubeMap(
          "application/res/textures/skybox/space/front.png",
          "application/res/textures/skybox/space/left.png",
          "application/res/textures/skybox/space/back.png",
          "application/res/textures/skybox/space/bottom.png",
          "application/res/textures/skybox/space/right.png",
          "application/res/textures/skybox/space/top.png"),
      m_cubeMapShader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag")
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : GLApplication(title, width, height, fullScreen),
      m_sphere(1, 64, 32),
      m_sphereShader("application/res/shaders/3D.vert", "application/res/shaders/directionallight.frag"),
      m_cubeMap(
          "application/res/textures/skybox/space/front.png",
          "application/res/textures/skybox/space/left.png",
          "application/res/textures/skybox/space/back.png",
          "application/res/textures/skybox/space/bottom.png",
          "application/res/textures/skybox/space/right.png",
          "application/res/textures/skybox/space/top.png"),
      m_cubeMapShader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag")
{
}

void Application::loop()
{
  // Print fps in console by passing true
  engine::TimeManager::getInstance().calculateFrameRate(false);

  // Get current context time
  float t = getWindowManager()->getTimeElapsed();

  // Render cube map
  getWindowManager()->getWindowUtils()->enableDepthTesting(false);
  m_cubeMap.render(getCamera(), m_cubeMapShader, t);
  getWindowManager()->getWindowUtils()->enableDepthTesting(true);

  // Render Sphere
  m_sphere.render(getCamera(), m_sphereShader, t);
}