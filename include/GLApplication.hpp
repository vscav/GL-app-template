#pragma once
#ifndef _GLApplication_HPP_
#define _GLApplication_HPP_

#include "TimeManager.hpp"
#include "FreeflyCamera.hpp"
#include "InputManager.hpp"
#include "WindowManager.hpp"

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

  WindowManager *m_windowManager;

  InputManager *m_inputManager;

  Camera *m_camera;

  float m_time;
  float m_deltaTime;

  void initialize(std::string title, int width, int height, bool fullScreen);

protected:
  GLApplication(const GLApplication &);

  GLApplication(std::string title, int width, int height, bool fullScreen);

  virtual void loop();

public:
  GLApplication();

  static GLApplication &getInstance();

  // window control
  void exit();

  // delta time between frame and time from beginning
  float getFrameDeltaTime() const;
  float getTime() const;

  // GLApplication run
  void run();

  inline void setWindowManager(WindowManager *windowManager) { m_windowManager = windowManager; }
  inline WindowManager *getWindowManager() const { return m_windowManager; }

  inline void setCamera(Camera *camera) { m_camera = camera; };
  inline Camera *getCamera() const { return m_camera; };

  inline void setInputManager(InputManager *inputManager) { m_inputManager = inputManager; };
  inline InputManager *getInputManager() const { return m_inputManager; };
};

#endif /* _GLApplication_HPP_ */
