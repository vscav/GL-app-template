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
  //std::unique_ptr<GLWindowManager> m_windowManager;

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
  ~GLApplication();

  static GLApplication &getInstance();

  void exit();

  float getFrameDeltaTime() const;
  float getTime() const;

  void run();

  inline void setWindowManager(GLWindowManager *windowManager) { m_windowManager = windowManager; }
  inline GLWindowManager *getWindowManager() const { return m_windowManager; }
  // const GLWindowManager *getWindowManager() const;
  // std::unique_ptr<GLWindowManager> setWindowManager(std::unique_ptr<GLWindowManager> windowManager);

  inline void setCamera(Camera *camera) { m_camera = camera; };
  inline Camera *getCamera() { return m_camera; };
};

#endif /* _GLApplication_HPP_ */
