#ifndef _Game_HPP_
#define _Game_HPP_

#include "GLApplication.hpp"
#include "Shader.hpp"
#include "FreeflyCamera.hpp"
#include "Sphere.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Game : public GLApplication
{
private:
  float m_time = 0.f;
  const int m_size = 100;

  std::vector<Sphere> m_spheres;

  GLint m_MVPMatrixLocation;
  GLint m_MVMatrixLocation;
  GLint m_NormalMatrixLocation;

  glm::mat4 m_ProjMatrix = glm::mat4(1.0);
  glm::mat4 m_MVMatrix = glm::translate(glm::mat4(1), glm::vec3(1.0));
  glm::mat4 m_NormalMatrix = glm::transpose(glm::inverse(m_MVMatrix));

  // FreeflyCamera camera;

  GLuint m_vao, m_vbo, m_ibo;

protected:
  virtual void loop();

public:
  Game();
};

#endif /* _Game_HPP_ */
