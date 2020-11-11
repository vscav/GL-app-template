#include "../header/GLApplication.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

using namespace std;

GLApplication *currentGLApplication = NULL;

GLApplication &GLApplication::getInstance()
{
  if (currentGLApplication)
    return *currentGLApplication;
  else
    throw std::runtime_error("There is no current GLApplication");
}

GLApplication::GLApplication()
    : m_state(stateReady), m_width(800), m_height(600), m_title("GLApplication")
{
  currentGLApplication = this;

  cout << "[Info] GLFW initialisation" << endl;

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
    throw std::runtime_error(string("Could initialize GLEW, error = ") + (const char *)glewGetErrorString(err));
  }

  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  cout << "Renderer: " << renderer << endl;
  cout << "OpenGL version supported " << version << endl;

  // opengl configuration
  glEnable(GL_DEPTH_TEST);
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

    detectWindowDimensionChange();

    loop();

    glfwSwapBuffers(m_window);

    glfwPollEvents();
  }

  glfwTerminate();
}

void GLApplication::detectWindowDimensionChange()
{
  int w, h;
  glfwGetWindowSize(getWindow(), &w, &h);
  m_dimensionChanged = (w != m_width or h != m_height);
  if (m_dimensionChanged)
  {
    m_width = w;
    m_height = h;
    glViewport(0, 0, m_width, m_height);
  }
}

void GLApplication::loop()
{
  cout << "[INFO] : loop" << endl;
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

bool GLApplication::windowDimensionChanged()
{
  return m_dimensionChanged;
}
