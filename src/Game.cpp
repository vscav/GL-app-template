#include "../include/Game.hpp"
#include "../include/GLError.hpp"
#include "../include/FilePath.hpp"
#include "../include/Program.hpp"
#include "../include/Sphere.hpp"

#include <iostream>

Game::Game()
    : GLApplication(),
      m_ProjMatrix(glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 100.f)),
      m_MVMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, -5))),
      m_NormalMatrix(glm::transpose(glm::inverse(m_MVMatrix))),
      m_sphere(new Sphere(1, 64, 32))
{
  glCheckError(__FILE__, __LINE__);

  // Shaders
  FilePath applicationPath("../");

  Program program = loadProgram(
      applicationPath + "shader/3D.vs.glsl",
      applicationPath + "shader/pointlight.fs.glsl");
  program.use();

  // Get shader program's ID
  const GLuint programId = program.getGLId();

  m_uLightIntensity = glGetUniformLocation(programId, "uLightIntensity");
  m_uLightPos_vs = glGetUniformLocation(programId, "uLightPos_vs");
  m_uKd = glGetUniformLocation(programId, "uKd");
  m_uKs = glGetUniformLocation(programId, "uKs");
  m_uShininess = glGetUniformLocation(programId, "uShininess");

  m_uMVPMatrix = glGetUniformLocation(programId, "uMVPMatrix");
  m_uMVMatrix = glGetUniformLocation(programId, "uMVMatrix");
  m_uNormalMatrix = glGetUniformLocation(programId, "uNormalMatrix");

  m_ProjMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 100.f);
  m_MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
  m_NormalMatrix = glm::transpose(glm::inverse(m_MVMatrix));
}

void Game::loop()
{
  TimeManager::Instance().calculateFrameRate(true);

  float t = getTime();

  // Clear GL window
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Get the ViewMatrix
  glm::mat4 MVMatrix = getCamera()->getViewMatrix();

  // Planet Earth animation
  glm::mat4 earthMVMatrix = glm::rotate(MVMatrix, t, glm::vec3(0, 1, 0)); // Translation * Rotation

  // Send matrices to the GPU
  glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
  glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
  glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix * earthMVMatrix));

  // Light settings
  // glm::mat4 lightMVMatrix = glm::rotate(MVMatrix, t, glm::vec3(0, 1, 0));
  // lightMVMatrix = glm::scale(lightMVMatrix, glm::vec3(1.25));
  // glm::vec3 lightPos(2, 2 * (glm::cos(t) * glm::sin(t)), 0);
  // glm::vec3 lightPos_vs(lightMVMatrix * glm::vec4(lightPos, 1));

  glm::vec3 lightPos_vs(MVMatrix * glm::vec4(1));

  // Send matrices on the GPU
  glUniform3f(m_uLightIntensity, 1, 1, 1);
  glUniform3fv(m_uLightPos_vs, 1, glm::value_ptr(lightPos_vs));
  glUniform3f(m_uKd, 0.35, 0, 1);
  glUniform3f(m_uKs, 0.85, 0, 1);
  glUniform1f(m_uShininess, 5);

  m_sphere->render();

  glCheckError(__FILE__, __LINE__);
}
