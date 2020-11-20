#pragma once
#ifndef _GLApplication_HPP_
#define _GLApplication_HPP_

#include "TimeManager.hpp"
#include "FreeflyCamera.hpp"
#include "InputManager.hpp"
#include "GLWindowManager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string>

struct GLFWwindow;

class GLApplication
{
private:
  enum State
  {
    stateReady,
    stateRun,
    stateExit
  };

  State m_state;

  GLApplication &operator=(const GLApplication &) { return *this; }

  GLWindowManager *m_windowManager;

  InputManager *m_inputManager;

  Camera *m_camera;

  float m_time;
  float m_deltaTime;

  void initialize(std::string title, int width, int height, bool fullScreen);

protected:
  GLApplication(const GLApplication &);

  virtual void loop();

public:
  GLApplication();
  GLApplication(std::string title, int width, int height, bool fullScreen);
  ~GLApplication() = default;

  static GLApplication &getInstance();

  // window control
  void exit();

  // delta time between frame and time from beginning
  float getFrameDeltaTime() const;
  float getTime() const;

  // GLApplication run
  void run();

  inline void setWindowManager(GLWindowManager *windowManager) { m_windowManager = windowManager; }
  inline GLWindowManager *getWindowManager() const { return m_windowManager; }

  inline void setCamera(Camera *camera) { m_camera = camera; };
  inline Camera *getCamera() const { return m_camera; };

  inline void setInputManager(InputManager *inputManager) { m_inputManager = inputManager; };
  inline InputManager *getInputManager() const { return m_inputManager; };
};

#endif /* _GLApplication_HPP_ */
