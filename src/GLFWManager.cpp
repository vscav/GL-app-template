#include "../include/GLFWManager.hpp"
#include "../include/GLApplication.hpp"

#include <iostream>

GLFWManager::GLFWManager()
{
    initialize();
}

GLFWManager::GLFWManager(int width, int height, std::string strTitle, bool bFullScreen)
    : m_width(width), m_height(height), m_strTitle(strTitle), m_bFullScreen(bFullScreen)
{
    initialize();
}

// This initializes our window and creates the OpenGL context
int GLFWManager::initialize()
{
    std::cout << "[Info] GLFW initialisation" << std::endl;

    // This tries to first init the GLFW library and make sure it is available
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

    // Create a window either in full screen or not
    if (m_bFullScreen)
        m_window = glfwCreateWindow(m_width, m_height, m_strTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else
        m_window = glfwCreateWindow(m_width, m_height, m_strTitle.c_str(), nullptr, nullptr);

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

    // We want to hide the mouse since it will be used to move the camera's view around
    // and don't want to see it being pushed up into the top left corner.
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the cursor position of the hidden mouse to be in the top left of the window.
    // This way we can get a delta of the mouse position from (0, 0) and reset it again.
    //glfwSetCursorPos(m_window, 0, 0);

    // This turns off the vertical sync to your monitor so it renders as fast as possible
    glfwSwapInterval(0);

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

    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;

    // opengl configuration
    glEnable(GL_DEPTH_TEST);

    InputManager *inputManager = new InputManager();
    setInputManager(inputManager);

    // Return success
    return 0;
}

// This swaps the backbuffer with the front buffer to display the content rendered in OpenGL
void GLFWManager::swapBuffers()
{
    // This takes the Window and swaps the backbuffer to the front
    glfwSwapBuffers(m_window);
}

// This function processes all the application's input and returns a bool to tell us if we should continue
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

        std::cout << m_firstMouse << std::endl;

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

// This destroys the window
void GLFWManager::destroy()
{
    // This closes the OpenGL window and terminates the application
    glfwTerminate();
}