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

  // GLFWwindow *m_window;

  WindowManager *m_windowManager;

  InputManager *m_inputManager;

  FreeflyCamera *m_camera;

  // Time:
  float m_time;
  float m_deltaTime;

  // Dimensions:
  int m_width;
  int m_height;

protected:
  GLApplication(const GLApplication &){};

  std::string m_title;

  virtual void loop();

public:
  GLApplication();

  static GLApplication &getInstance();

  // get the window id
  // GLFWwindow *getWindow() const;

  // window control
  void exit();

  // delta time between frame and time from beginning
  float getFrameDeltaTime() const;
  float getTime() const;

  // GLApplication run
  void run();

  // GLApplication informations
  int getWidth();
  int getHeight();
  float getWindowRatio();

  inline void setWindowManager(WindowManager *windowManager) { m_windowManager = windowManager; }
  inline WindowManager *getWindowManager() const { return m_windowManager; }

  inline void setCamera(FreeflyCamera *camera) { m_camera = camera; };
  inline FreeflyCamera *getCamera() const { return m_camera; };

  inline void setInputManager(InputManager *inputManager) { m_inputManager = inputManager; };
  inline InputManager *getInputManager() const { return m_inputManager; };

  // void ProcessInput();
};

#endif /* _GLApplication_HPP_ */
