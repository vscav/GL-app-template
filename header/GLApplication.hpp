#ifndef _GLApplication_HPP_
#define _GLApplication_HPP_

#include "../header/TimeManager.hpp"
#include "../header/FreeflyCamera.hpp"
#include "../header/InputManager.hpp"

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

  GLFWwindow *m_window;

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
  GLFWwindow *getWindow() const;

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

  void setCamera(FreeflyCamera *camera) { m_camera = camera; };
  FreeflyCamera *getCamera() { return m_camera; };

  void setInputManager(InputManager *inputManager) { m_inputManager = inputManager; };
  InputManager *getInputManager() { return m_inputManager; };

  void ProcessInput();
};

#endif /* _GLApplication_HPP_ */
