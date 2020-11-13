#ifndef _GLFWManager_HPP_
#define _GLFWManager_HPP_

#include "WindowManager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>

// This is our implementation of the abstract base class WindowManager, which uses the
// GLFW cross-platform library to create a window, handle input and create the OpenGL
// context.
class GLFWManager : public WindowManager
{
public:
    // Create an empty constructor and have the deconstructor release our memory
    GLFWManager();
    GLFWManager(int width, int height, std::string strTitle, bool bFullScreen);
    inline ~GLFWManager() { destroy(); };

    // This initialized the window and creates the OpenGL context
    virtual int initialize() override;

    // This swaps the backbuffer to the front and should be called every frame
    virtual void swapBuffers() override;

    // This processes any needed input for the application, like the Escape key
    virtual void processInput() override;

    // This destroys the window and OpenGL context
    virtual void destroy();

    // Add a way to access and get the application's window
    // inline GLFWwindow *getWindow() const { return m_window; }

protected:
    // This is the GLFW window object that manages the window and input
    GLFWwindow *m_window;

    std::string m_strTitle = "GL-app-template";
    int m_width = 800;
    int m_height = 600;
    bool m_bFullScreen = false;
};

#endif /* _GLFWManager_HPP_ */