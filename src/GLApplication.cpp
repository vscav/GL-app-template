#include "../include/GLApplication.hpp"
#include "../include/manager/GLFWManager.hpp"

GLApplication *currentGLApplication = NULL;

GLApplication &GLApplication::getInstance()
{
  if (currentGLApplication)
    return *currentGLApplication;
  else
    throw std::runtime_error("There is no current GLApplication");
}

GLApplication::GLApplication()
    : m_state(stateReady),
      m_windowManager(new manager::GLFWManager("GLApplication", 1600, 900, false)),
      m_camera(new world::FreeflyCamera())
{
  currentGLApplication = this;
}

GLApplication::GLApplication(std::string title, int width, int height, bool fullScreen)
    : m_state(stateReady),
      m_windowManager(new manager::GLFWManager(title, width, height, fullScreen)),
      m_camera(new world::FreeflyCamera())
{
  currentGLApplication = this;
};

void GLApplication::exit()
{
  std::cout << "[GLApplication] Application exited successfully" << std::endl;

  m_state = stateExit;
}

void GLApplication::run()
{
  m_state = stateRun;

  while (m_state == stateRun)
  {
    getWindowManager()->update();

    getWindowManager()->processInput();

    loop();

    getWindowManager()->swapBuffers();
  }
}

void GLApplication::loop()
{
  std::cout << "[Info] GLApplication main loop" << std::endl;
}