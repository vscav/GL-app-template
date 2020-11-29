#pragma once
#ifndef _Application_HPP_
#define _Application_HPP_

#include "GLApplication.hpp"
#include "opengl/Shader.hpp"
#include "world/FreeflyCamera.hpp"
#include "world/Sphere.hpp"
#include "world/CubeMap.hpp"

#include "dependencies/glm.hpp"

#include <GLFW/glfw3.h>

/// \class Application
/// \brief Class which inherites from the global GLApplication class.
class Application : public GLApplication
{
private:
  world::Sphere m_sphere;               /*!< A sphere object. */
  opengl::Shader m_sphereShader; /*!< The shaders which will be used for the sphere object. */

  world::CubeMap m_cubeMap;              /*!< A cube map object. */
  opengl::Shader m_cubeMapShader; /*!< The shaders which will be used for the cube map object. */

protected:
  /// \brief The application loop (run until the user asks to quit).
  virtual void loop();

public:
  /// \brief Constructor.
  Application();
  /// \brief Parameterized Constructor.
  /// \param title : The application title (string).
  /// \param width : The application width value.
  /// \param height : The application height value.
  /// \param fullScreen : A boolean to determine if the application window is in full screen mode.
  Application(std::string title, int width, int height, bool fullScreen);
  /// \brief Destructor.
  ~Application();
};

#endif /* _Application_HPP_ */
