#pragma once
#ifndef _GLApplication_HPP_
#define _GLApplication_HPP_

#include <engine/TimeManager.hpp>
#include <engine/GLWindowManager.hpp>
#include <engine/FreeflyCamera.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

namespace engine
{

  /// \class GLApplication
  /// \brief Class which represents the core of the OpenGL application.
  class GLApplication
  {
  private:
    /// \brief The different states in which the application can be found.
    enum State
    {
      stateReady,
      stateRun,
      stateExit
    };

    State m_state; /*!< The current state of the GL application (ready, run or exit). */

    /// \brief Affectation/Copy assignment operator.
    GLApplication &operator=(const GLApplication &) = delete;

    std::unique_ptr<GLWindowManager> m_windowManager; /*!< A unique pointer to the window manager of the application. */
    std::unique_ptr<Camera> m_camera;                 /*!< A unique pointer to the camera used by the application. */

  protected:
    /// \brief Copy constructor.
    GLApplication(const GLApplication &) = delete;
    /// \brief The GL application loop (run until the user asks to quit).
    virtual void loop();

  public:
    /// \brief Constructor.
    GLApplication();
    /// \brief Parameterized constructor.
    /// \param title : The GL application title (string).
    /// \param width : The GL application width value.
    /// \param height : The GL application height value.
    /// \param fullScreen : A boolean to determine if the GL application window is in full screen mode.
    GLApplication(std::string title, int width, int height, bool fullScreen);
    virtual ~GLApplication() = default;

    /// \brief Returns the current GL application instance.
    /// \return The instance of the current application.
    static GLApplication &getInstance();

    /// \brief Exits the GL application by changing the current state.
    void exit();

    /// \brief Runs the GL application by changing the current state and starting the GL application main loop.
    void run();

    /// \brief Returns the window manager (pointer) of the GL application.
    /// \return A pointer to the window manager of the GL application.
    inline GLWindowManager *getWindowManager() const { return m_windowManager.get(); }
    /// \brief Returns the camera (pointer) of the GL application.
    /// \return A pointer to the camera of the GL application.
    inline Camera *getCamera() { return m_camera.get(); };
  };

} // namespace engine

#endif /* _GLApplication_HPP_ */