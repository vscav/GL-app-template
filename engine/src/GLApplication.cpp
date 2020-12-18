#include <engine/GLApplication.hpp>
#include <engine/GLFWManager.hpp>
#include <engine/Renderer.hpp>
#include <engine/utils/common.hpp>

namespace engine
{

  GLApplication *currentGLApplication = nullptr;

  GLApplication &GLApplication::getInstance()
  {
    if (currentGLApplication)
      return *currentGLApplication;
    else
      throw std::runtime_error("There is no current GLApplication");
  }

  GLApplication::GLApplication()
      : m_state(stateReady),
        m_windowManager(new GLFWManager()),
        m_camera(new FreeflyCamera())
  {
    Renderer::getInstance().setCamera(m_camera);
    currentGLApplication = this;
  }

  GLApplication::GLApplication(std::string title, int width, int height, bool fullScreen)
      : m_state(stateReady),
        m_windowManager(new GLFWManager(title, width, height, fullScreen)),
        m_camera(new FreeflyCamera())
  {
    Renderer::getInstance().setCamera(m_camera);
    currentGLApplication = this;
  }

  void GLApplication::exit()
  {
    if(debug) std::cout << "[GLApplication] Application exited successfully" << std::endl;

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
    if(debug) std::cout << "[Info] GLApplication main loop" << std::endl;
  }

} // namespace engine