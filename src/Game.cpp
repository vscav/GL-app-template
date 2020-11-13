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
      m_NormalMatrix(glm::transpose(glm::inverse(m_MVMatrix)))
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

  Sphere sphere(1, 64, 32);
  m_spheres.push_back(sphere);

  // VBO creation
  // GLuint vbo;
  glGenBuffers(1, &m_vbo);

  // VBO binding
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  // Send data (related to the sphere) into the VBO
  glBufferData(GL_ARRAY_BUFFER, m_spheres[0].getVertexCount() * sizeof(ShapeVertex), m_spheres[0].getDataPointer(), GL_STATIC_DRAW);

  // Unbind the VBO (to avoid errors)
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // VAO creation
  // GLuint vao;
  glGenVertexArrays(1, &m_vao);

  // VAO binding
  glBindVertexArray(m_vao);

  // Vertex attributs position
  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_NORMAL = 1;
  const GLuint VERTEX_ATTR_TEXCOORD = 2;

  // Enable vertex attributes array
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
  glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

  // Activation of vertex attributs
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  // Define arrays of attribute data
  glVertexAttribPointer(
      VERTEX_ATTR_POSITION,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(ShapeVertex),
      (const GLvoid *)offsetof(ShapeVertex, position));
  glVertexAttribPointer(
      VERTEX_ATTR_NORMAL,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(ShapeVertex),
      (const GLvoid *)offsetof(ShapeVertex, normal));
  glVertexAttribPointer(
      VERTEX_ATTR_TEXCOORD,
      2,
      GL_FLOAT,
      GL_FALSE,
      sizeof(ShapeVertex),
      (const GLvoid *)offsetof(ShapeVertex, texCoords));

  // Unbind the VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Unbind the VAO
  glBindVertexArray(0);
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

  // Bind the VAO
  glBindVertexArray(m_vao);
  // Drawing call
  glDrawArrays(GL_TRIANGLES, 0, m_spheres[0].getVertexCount());
  // Unbind the VAO
  glBindVertexArray(0);

  glCheckError(__FILE__, __LINE__);
}
