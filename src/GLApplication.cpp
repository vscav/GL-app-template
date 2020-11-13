#include "../header/GLApplication.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

GLApplication *currentGLApplication = NULL;

GLApplication &GLApplication::getInstance()
{
  if (currentGLApplication)
    return *currentGLApplication;
  else
    throw std::runtime_error("There is no current GLApplication");
}

GLApplication::GLApplication()
    : m_state(stateReady), m_width(1200), m_height(720), m_title("GLApplication")
{
  currentGLApplication = this;

  std::cout << "[Info] GLFW initialisation" << std::endl;

  if (!glfwInit())
  {
    throw std::runtime_error("Couldn't init GLFW");
  }

  int major = 3;
  int minor = 2;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
  if (!m_window)
  {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window");
  }

  glfwMakeContextCurrent(m_window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK)
  {
    glfwTerminate();
    throw std::runtime_error(std::string("Could initialize GLEW, error = ") + (const char *)glewGetErrorString(err));
  }

  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported " << version << std::endl;

  // opengl configuration
  glEnable(GL_DEPTH_TEST);

  FreeflyCamera *camera = new FreeflyCamera();
  setCamera(camera);

  InputManager *inputManager = new InputManager();
  setInputManager(inputManager);

  getInputManager()->setCamera(camera);
}

GLFWwindow *GLApplication::getWindow() const
{
  return m_window;
}

void GLApplication::exit()
{
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

  glfwMakeContextCurrent(m_window);

  m_time = glfwGetTime();

  while (m_state == stateRun)
  {
    float t = glfwGetTime();
    m_deltaTime = t - m_time;
    m_time = t;

    ProcessInput();

    loop();

    glfwSwapBuffers(m_window);
  }

  glfwTerminate();
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

void GLApplication::ProcessInput()
{
  if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_window) != 0)
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);

  if (glfwGetKey(m_window, GLFW_KEY_UP) || glfwGetKey(m_window, GLFW_KEY_W))
    getInputManager()->KeyPressed(InputCodes::Up);
  if (glfwGetKey(m_window, GLFW_KEY_DOWN) || glfwGetKey(m_window, GLFW_KEY_S))
    getInputManager()->KeyPressed(InputCodes::Down);
  if (glfwGetKey(m_window, GLFW_KEY_LEFT) || glfwGetKey(m_window, GLFW_KEY_A))
    getInputManager()->KeyPressed(InputCodes::Left);
  if (glfwGetKey(m_window, GLFW_KEY_RIGHT) || glfwGetKey(m_window, GLFW_KEY_D))
    getInputManager()->KeyPressed(InputCodes::Right);

  glfwPollEvents();
}
