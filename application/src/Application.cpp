#include <engine/FreeflyCamera.hpp>
#include <engine/TrackballCamera.hpp>
#include <engine/GLFWManager.hpp>

#include "../include/Application.hpp"
#include "../include/utils/directory.hpp"

#include <string>

Application::Application()
    : engine::GLApplication(new engine::TrackballCamera(), new engine::GLFWManager()),
      m_sphere(1, 64, 32),
      m_sphereShader("application/res/shaders/forward.vert", "application/res/shaders/directionallight.frag"),
      m_cubeMap(
          "application/res/textures/skybox/space/front.png",
          "application/res/textures/skybox/space/left.png",
          "application/res/textures/skybox/space/back.png",
          "application/res/textures/skybox/space/bottom.png",
          "application/res/textures/skybox/space/right.png",
          "application/res/textures/skybox/space/top.png"),
      m_cubeMapShader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag"),
      m_model("application/res/models/spaceship/scene.gltf"),
      m_modelShader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag")
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : engine::GLApplication(new engine::FreeflyCamera(), new engine::GLFWManager(), title, width, height, fullScreen),
      m_sphere(1, 64, 32),
      m_sphereShader("application/res/shaders/forward.vert", "application/res/shaders/directionallight.frag"),
      m_cubeMap(
          "application/res/textures/skybox/space/front.png",
          "application/res/textures/skybox/space/left.png",
          "application/res/textures/skybox/space/back.png",
          "application/res/textures/skybox/space/bottom.png",
          "application/res/textures/skybox/space/right.png",
          "application/res/textures/skybox/space/top.png"),
      m_cubeMapShader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag"),
      m_model("application/res/models/spaceship/scene.gltf"),
      m_modelShader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag")
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
  // m_sphere.render(getCamera(), m_sphereShader, t);

  // Render Model
  m_model.render(getCamera(), m_modelShader, t);
}