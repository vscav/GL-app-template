#include "../include/GLApplication.hpp"
#include "../include/WindowManager.hpp"
#include "../include/GLFWManager.hpp"

GLApplication *currentGLApplication = NULL;

GLApplication &GLApplication::getInstance()
{
  if (currentGLApplication)
    return *currentGLApplication;
  else
    throw std::runtime_error("There is no current GLApplication");
}

GLApplication::GLApplication()
    : m_state(stateReady), m_width(1600), m_height(900), m_title("GLApplication")
{
  currentGLApplication = this;
  
  GLFWManager *windowManager = new GLFWManager(m_width, m_height, m_title, false);
  setWindowManager(windowManager);

  FreeflyCamera *camera = new FreeflyCamera();
  setCamera(camera);

  getWindowManager()->getInputManager()->setCamera(camera);
}

void GLApplication::exit()
{
  std::cout << "Application exited successfully" << std::endl;

  glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);

  m_state = stateExit;
}

float GLApplication::getFrameDeltaTime() const
{
  return m_deltaTime;
}

float GLApplication::getTime() const
{
  return m_time;
}

void GLApplication::run()
{
  m_state = stateRun;

  // glfwMakeContextCurrent(m_window);

  m_time = glfwGetTime();

  while (m_state == stateRun)
  {
    float t = glfwGetTime();
    m_deltaTime = t - m_time;
    m_time = t;

    getWindowManager()->processInput();

    loop();

    getWindowManager()->swapBuffers();
  }
}

void GLApplication::loop()
{
  std::cout << "[INFO] : loop" << std::endl;
}

int GLApplication::getWidth()
{
  return m_width;
}

int GLApplication::getHeight()
{
  return m_height;
}

float GLApplication::getWindowRatio()
{
  return float(m_width) / float(m_height);
}
