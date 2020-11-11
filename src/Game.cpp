#include "../header/Game.hpp"
#include "../header/GLError.hpp"
#include "../header/FilePath.hpp"
#include "../header/Program.hpp"
#include "../header/Sphere.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

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
      applicationPath + "shader/normals.fs.glsl");
  program.use();

  // Get program's ID
  const GLuint programId = program.getGLId();

  // Get uniforms location
  m_MVPMatrixLocation = glGetUniformLocation(programId, "uMVPMatrix");
  m_MVMatrixLocation = glGetUniformLocation(programId, "uMVMatrix");
  m_NormalMatrixLocation = glGetUniformLocation(programId, "uNormalMatrix");

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
  // exit on window close button pressed
  if (glfwWindowShouldClose(getWindow()))
    exit();

  float t = getTime();
  // set matrix : projection + view

  // clear
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Send matrices to the GPU
  glUniformMatrix4fv(m_MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix * m_MVMatrix));
  glUniformMatrix4fv(m_MVMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_MVMatrix));
  glUniformMatrix4fv(m_NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_NormalMatrix));

  // Bind the VAO
  glBindVertexArray(m_vao);
  // Drawing call
  glDrawArrays(GL_TRIANGLES, 0, m_spheres[0].getVertexCount());
  // Unbind the VAO
  glBindVertexArray(0);

  glCheckError(__FILE__, __LINE__);
}
