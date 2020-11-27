#include "../include/GLApplication.hpp"
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
    : m_state(stateReady)
{
  initialize("GLApplication", 1600, 900, false);
}

GLApplication::GLApplication(std::string title, int width, int height, bool fullScreen)
    : m_state(stateReady)
{
  initialize(title, width, height, fullScreen);
};

GLApplication::~GLApplication()
{
  delete m_camera;
  delete m_windowManager;
}

void GLApplication::initialize(std::string title, int width, int height, bool fullScreen)
{
  currentGLApplication = this;

  GLFWManager *windowManager = new GLFWManager(title, width, height, false);
  setWindowManager(windowManager);

  // std::unique_ptr<GLWindowManager> windowManager(new GLFWManager(title, width, height, false));
  // setWindowManager(windowManager);

  FreeflyCamera *camera = new FreeflyCamera();
  setCamera(camera);

  // std::unique_ptr<Camera> camera(new FreeflyCamera());
  // setCamera(camera);
}

// const GLWindowManager *GLApplication::getWindowManager() const
// {
//   return m_windowManager.get();
// };

// std::unique_ptr<GLWindowManager> GLApplication::setWindowManager(std::unique_ptr<GLWindowManager> windowManager)
// {
//   std::unique_ptr<GLWindowManager> old = std::move(m_windowManager);
//   m_windowManager = std::move(windowManager);
//   return std::move(old);
// };

// const Camera *GLApplication::getCamera() const
// {
//   return m_camera.get();
// };

// std::unique_ptr<Camera> GLApplication::setCamera(std::unique_ptr<Camera> camera)
// {
//   std::unique_ptr<Camera> old = std::move(m_camera);
//   m_camera = std::move(camera);
//   return std::move(old);
// };

void GLApplication::exit()
{
  std::cout << "[GLApplication] Application exited successfully" << std::endl;

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

  while (m_state == stateRun)
  {
    float t = glfwGetTime();

    m_deltaTime = t - m_time;
    m_time = t;

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
