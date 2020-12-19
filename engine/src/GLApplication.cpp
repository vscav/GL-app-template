#include <engine/GLApplication.hpp>
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

  GLApplication::GLApplication(Camera* camera, GLWindowManager* manager)
      : m_state(stateReady),
        m_windowManager(manager),
        m_camera(camera)
  {
    Renderer::getInstance().setCamera(m_camera);
    currentGLApplication = this;
  }

  GLApplication::GLApplication(Camera* camera, GLWindowManager* manager, std::string title, int width, int height, bool fullScreen)
      : m_state(stateReady),
        m_windowManager(manager),
        m_camera(camera)
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