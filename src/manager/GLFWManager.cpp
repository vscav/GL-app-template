#include "../../include/GLApplication.hpp"
#include "../../include/manager/GLFWManager.hpp"

#include <iostream>

namespace manager
{

    GLFWManager::GLFWManager(std::string title, int width, int height, bool fullScreen)
        : m_title(title), m_width(width), m_height(height), m_fullScreen(fullScreen)
    {
        initialize();
    }

    // This initializes our window and creates the OpenGL context
    int GLFWManager::initialize()
    {
        std::cout << "[GLFWManager] GLFW initialisation" << std::endl;

        if (!glfwInit())
        {
            throw std::runtime_error("Couldn't init GLFW");
        }

        getContext();

        createWindow();

        // Tell GLEW to grab all the OpenGL functions and extensions even if "experimental"
        glewExperimental = GL_TRUE;

        // Initialize the GLEW library and attach all the OpenGL functions and extensions
        GLenum err = glewInit();

        // If we had an error, return -1.  Be sure to see if glewExperimental isn't true, this worked for me.
        if (GLEW_OK != err)
        {
            glfwTerminate();
            throw std::runtime_error(std::string("Could initialize GLEW, error = ") + (const char *)glewGetErrorString(err));
        }
        else
        {
            std::cout << "[GLFWManager] GLFW window successfully created" << std::endl;
        }

        // get version info
        const GLubyte *renderer = glGetString(GL_RENDERER);
        const GLubyte *version = glGetString(GL_VERSION);
        std::cout << "[Info] Renderer: " << renderer << std::endl;
        std::cout << "[Info] Version supported: " << version << std::endl;

        InputManager *inputManager = new InputManager();
        setInputManager(inputManager);

        utils::GLWindowUtils *windowUtils = new utils::GLWindowUtils();
        setWindowUtils(windowUtils);

        // opengl configuration : enable depth test
        m_windowUtils->enableDepthTesting(true);

        // opengl configuration : antialiasing
        m_windowUtils->antialias(true);

        // Return success
        return 0;
    }

    void GLFWManager::getContext()
    {
        int major = 3;
        int minor = 3;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void GLFWManager::createWindow()
    {
        m_monitor = glfwGetPrimaryMonitor();

        if (m_fullScreen)
        {
            const GLFWvidmode *mode = glfwGetVideoMode(m_monitor);

            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            m_height = mode->height;
            m_width = mode->width;

            m_window = glfwCreateWindow(mode->width, mode->height, m_title.c_str(), m_monitor, nullptr);
        }
        else
        {
            m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
            centerWindow();
        }

        // Make sure the window is valid, if not, throw an error.
        if (m_window == nullptr)
        {
            glfwTerminate();
            throw std::runtime_error("Couldn't create a window");
        }

        // Create the OpenGL context from the window and settings specified
        glfwMakeContextCurrent(m_window);

        // This turns on STICKY_KEYS for keyboard input
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

        // This turns off the vertical sync to your monitor so it renders as fast as possible
        glfwSwapInterval(0);
    }

    void GLFWManager::centerWindow()
    {
        if (m_monitor == nullptr)
            return;

        const GLFWvidmode *mode = glfwGetVideoMode(m_monitor);
        if (!mode)
            return;

        int monitorX, monitorY;
        glfwGetMonitorPos(m_monitor, &monitorX, &monitorY);

        glfwSetWindowPos(m_window,
                         monitorX + (mode->width - m_width) / 2,
                         monitorY + (mode->height - m_height) / 2);
    }

    // This swaps the backbuffer with the front buffer to display the content rendered in OpenGL
    void GLFWManager::swapBuffers()
    {
        // This takes the Window and swaps the backbuffer to the front
        glfwSwapBuffers(m_window);
    }

    // This function processes all the application's input
    void GLFWManager::processInput()
    {
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_window) != 0)
        {
            GLApplication::getInstance().exit();
        }

        if (glfwGetKey(m_window, GLFW_KEY_UP) || glfwGetKey(m_window, GLFW_KEY_W))
            m_inputManager->keyPressed(InputCodes::Up);
        if (glfwGetKey(m_window, GLFW_KEY_DOWN) || glfwGetKey(m_window, GLFW_KEY_S))
            m_inputManager->keyPressed(InputCodes::Down);
        if (glfwGetKey(m_window, GLFW_KEY_LEFT) || glfwGetKey(m_window, GLFW_KEY_A))
            m_inputManager->keyPressed(InputCodes::Left);
        if (glfwGetKey(m_window, GLFW_KEY_RIGHT) || glfwGetKey(m_window, GLFW_KEY_D))
            m_inputManager->keyPressed(InputCodes::Right);

        int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(m_window, &xpos, &ypos);

            if (m_firstMouse)
            {
                m_lastX = xpos;
                m_lastY = ypos;
                m_firstMouse = false;
            }

            GLfloat xoffset = m_lastX - xpos;
            GLfloat yoffset = m_lastY - ypos;

            m_lastX = xpos;
            m_lastY = ypos;

            m_inputManager->mouseMoved(xoffset, yoffset);
        }

        glfwPollEvents();
    }

    void GLFWManager::update()
    {
        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        m_width = width;
        m_height = height;

        glViewport(0, 0, m_width, m_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    }

    float const GLFWManager::getTimeElapsed()
    {
        m_time = glfwGetTime();
        
        return m_time;
    }

    float const GLFWManager::getFrameDeltaTime()
    {
        m_deltaTime = getTimeElapsed() - m_time;

        return m_deltaTime;
    }

    // This destroys the window
    void GLFWManager::destroy()
    {
        glfwDestroyWindow(m_window);
        std::cout << "[GLFWManager] Destroy GLFW window" << std::endl;

        glfwTerminate();
    }

} // namespace manager