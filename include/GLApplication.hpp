#pragma once
#ifndef _GLApplication_HPP_
#define _GLApplication_HPP_

#include "TimeManager.hpp"
#include "FreeflyCamera.hpp"
#include "GLWindowManager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

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

  /// \brief Affectation operator.
  GLApplication &operator=(const GLApplication &) { return *this; }

  GLWindowManager *m_windowManager; /*!< A pointer to the window manager of the GL application. */
  // std::unique_ptr<GLWindowManager> m_windowManager;
  Camera *m_camera; /*!< A pointer to the camera of the GL application. */
  // std::unique_ptr<Camera> m_camera;

  float m_time;      /*!< The GL application total time ellapsed. */
  float m_deltaTime; /*!< The time difference between the previous frame that was drawn and the current frame. */

  /// \brief Initialize the GL application (create a window manager and a camera).
  /// \param title : The GL application title (string).
  /// \param width : The GL application width value.
  /// \param height : The GL application height value.
  /// \param fullScreen : A boolean to determine if the GL application window is in full screen mode.
  void initialize(std::string title, int width, int height, bool fullScreen);

protected:
  GLApplication(const GLApplication &);
  /// \brief The GL application loop (run until the user asks to quit).
  virtual void loop();

public:
  /// \brief Constructor.
  GLApplication();
  /// \brief Parameterized Constructor.
  /// \param title : The GL application title (string).
  /// \param width : The GL application width value.
  /// \param height : The GL application height value.
  /// \param fullScreen : A boolean to determine if the GL application window is in full screen mode.
  GLApplication(std::string title, int width, int height, bool fullScreen);
  ~GLApplication();

  /// \brief Return the current GL application instance.
  static GLApplication &getInstance();

  /// \brief Exit the GL application by changing the current state.
  void exit();

  /// \brief Return the delta time (the time difference between the previous frame that was drawn and the current frame).
  float getFrameDeltaTime() const;
  /// \brief Return the total time ellapsed since the GL application was started.
  float getTime() const;

  /// \brief Run the GL application by changing the current state and starting the GL application main loop.
  void run();

  /// \brief Set the window manager for the GL application.
  /// \param : A pointer to the window manager.
  inline void setWindowManager(GLWindowManager *windowManager) { m_windowManager = windowManager; }
  /// \brief Return the window manager (pointer) of the GL application.
  inline GLWindowManager *getWindowManager() const { return m_windowManager; }
  // const GLWindowManager *getWindowManager() const;
  // std::unique_ptr<GLWindowManager> setWindowManager(std::unique_ptr<GLWindowManager> windowManager);
  /// \brief Set the camera for the GL application.
  /// \param : A pointer to the camera.
  inline void setCamera(Camera *camera) { m_camera = camera; };
  /// \brief Return the camera (pointer) of the GL application.
  inline Camera *getCamera() { return m_camera; };
  // const Camera *getCamera() const;
  // std::unique_ptr<Camera> setCamera(std::unique_ptr<Camera> camera);
};

#endif /* _GLApplication_HPP_ */
