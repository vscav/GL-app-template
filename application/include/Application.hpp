#pragma once
#ifndef _Application_HPP_
#define _Application_HPP_

#include <engine/GLApplication.hpp>
#include <engine/Shader.hpp>
#include <engine/Sphere.hpp>
#include <engine/CubeMap.hpp>
#include <engine/Model.hpp>
#include <engine/Entity.hpp>

#include <engine/dependencies/glm.hpp>

#include <GLFW/glfw3.h>

/// \class Application
/// \brief Class which inherites from the global GLApplication class.
class Application : public engine::GLApplication
{

private:
  engine::CubeMap m_cubeMap; /*!< A cube map object. */

  engine::Entity m_entity; /*!< An entity map object. */

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