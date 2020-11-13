#ifndef _Game_HPP_
#define _Game_HPP_

#include "GLApplication.hpp"
#include "Shader.hpp"
#include "FreeflyCamera.hpp"
#include "Sphere.hpp"
#include "Program.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Game : public GLApplication
{
private:
  float m_time = 0.f;
  const int m_size = 100;

  std::vector<Sphere> m_spheres;

  glm::mat4 m_ProjMatrix = glm::mat4(1.0);
  glm::mat4 m_MVMatrix = glm::translate(glm::mat4(1), glm::vec3(1.0));
  glm::mat4 m_NormalMatrix = glm::transpose(glm::inverse(m_MVMatrix));

  GLint m_uMVPMatrix;
  GLint m_uMVMatrix;
  GLint m_uNormalMatrix;
  GLint m_uLightIntensity;
  GLint m_uLightPos_vs;
  GLint m_uKd;
  GLint m_uKs;
  GLint m_uShininess;

  GLuint m_vao, m_vbo, m_ibo;

protected:
  virtual void loop();

public:
  Game();
};

#endif /* _Game_HPP_ */
