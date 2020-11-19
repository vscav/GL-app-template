#include "../include/Game.hpp"
#include "../include/GLError.hpp"
#include "../include/FilePath.hpp"
// #include "../include/Program.hpp"
#include "../include/Sphere.hpp"

#include <iostream>

Game::Game()
    : GLApplication(),
      m_sphere(new Sphere(1, 64, 32)),
      m_sphereShader("../shader/3D.vert", "../shader/pointlight.frag")
{
}

void Game::loop()
{
  // Print fps in console
  TimeManager::Instance().calculateFrameRate(true);

  // Get current context time
  float t = getTime();

  // Clear GL window
  getWindowManager()->clear();

  // Render Sphere
  m_sphere->render(getCamera(), m_sphereShader);

  // Check for GL errors
  glCheckError(__FILE__, __LINE__);
}
