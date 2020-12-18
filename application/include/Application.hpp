#pragma once
#ifndef _Application_HPP_
#define _Application_HPP_

#include <engine/GLApplication.hpp>
#include <engine/Shader.hpp>
#include <engine/FreeflyCamera.hpp>
#include <engine/Sphere.hpp>
#include <engine/CubeMap.hpp>
#include <engine/Model.hpp>

#include <engine/dependencies/glm.hpp>

#include <GLFW/glfw3.h>

/// \class Application
/// \brief Class which inherites from the global GLApplication class.
class Application : public engine::GLApplication
{
private:
  engine::Sphere m_sphere;       /*!< A sphere object. */
  engine::Shader m_sphereShader; /*!< The shaders which will be used for the sphere object. */

  engine::CubeMap m_cubeMap;      /*!< A cube map object. */
  engine::Shader m_cubeMapShader; /*!< The shaders which will be used for the cube map object. */

  engine::Model m_model;        /*!< A model object. */
  engine::Shader m_modelShader; /*!< The shaders which will be used for the model object. */

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
  explicit Application(std::string title, int width, int height, bool fullScreen);
  /// \brief Destructor.
  virtual ~Application() = default;
};

#endif /* _Application_HPP_ */