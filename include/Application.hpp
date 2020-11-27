#pragma once
#ifndef _Application_HPP_
#define _Application_HPP_

#include "GLApplication.hpp"
#include "Shader.hpp"
#include "FreeflyCamera.hpp"
#include "Sphere.hpp"
#include "Program.hpp"

#include "./dependencies/glm.hpp"

#include <GLFW/glfw3.h>

/// \class Application
/// \brief Class which inherites from the global GLApplication class.
class Application : public GLApplication
{
private:
  Sphere m_sphere; /*!< A sphere object. */

  Shader m_sphereShader; /*!< The shaders which will be applied to the sphere object. */

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
