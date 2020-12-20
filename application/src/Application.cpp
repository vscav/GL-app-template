#include <engine/FreeflyCamera.hpp>
#include <engine/TrackballCamera.hpp>
#include <engine/GLFWManager.hpp>

#include "../include/Application.hpp"
#include "../include/utils/directory.hpp"

#include <string>

Application::Application()
    : engine::GLApplication(new engine::TrackballCamera(), new engine::GLFWManager()),
      m_cubeMap(
          "application/res/textures/skybox/space/front.png",
          "application/res/textures/skybox/space/left.png",
          "application/res/textures/skybox/space/back.png",
          "application/res/textures/skybox/space/bottom.png",
          "application/res/textures/skybox/space/right.png",
          "application/res/textures/skybox/space/top.png"),
      m_cubeMapShader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag"),
      m_entity(new engine::Model("application/res/models/spaceship/scene.gltf"), false),
      m_entityShader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag")
{
}

Application::Application(std::string title, int width, int height, bool fullScreen)
    : engine::GLApplication(new engine::TrackballCamera(), new engine::GLFWManager(), title, width, height, fullScreen),
      m_cubeMap(
          "application/res/textures/skybox/space/front.png",
          "application/res/textures/skybox/space/left.png",
          "application/res/textures/skybox/space/back.png",
          "application/res/textures/skybox/space/bottom.png",
          "application/res/textures/skybox/space/right.png",
          "application/res/textures/skybox/space/top.png"),
      m_cubeMapShader("application/res/shaders/skybox.vert", "application/res/shaders/skybox.frag"),
      m_entity(new engine::Model("application/res/models/spaceship/scene.gltf"), false),
      m_entityShader("application/res/shaders/forward.vert", "application/res/shaders/pbr_directionallight.frag")
{
}

void Application::loop()
{
  // Print fps in console by passing true
  engine::TimeManager::getInstance().calculateFrameRate(false);

  // Get current context time of the window
  float t = getWindowManager()->getTimeElapsed();

  // Render cube map
  getWindowManager()->getWindowUtils()->enableDepthTesting(false);
  m_cubeMap.render(getCamera(), m_cubeMapShader, t);
  getWindowManager()->getWindowUtils()->enableDepthTesting(true);

  // Render Entity
  // m_entity.moveLeft(t);
  m_entity.render(getCamera(), m_entityShader, t);
}