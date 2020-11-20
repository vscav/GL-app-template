#pragma once
#ifndef _GLFWManager_HPP_
#define _GLFWManager_HPP_

#include "GLWindowManager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>

// This is our implementation of the abstract base class WindowManager, which uses the
// GLFW cross-platform library to create a window, handle input and create the OpenGL
// context.
class GLFWManager : public GLWindowManager
{
protected:
    // This is the GLFW window object that manages the window and input
    GLFWwindow *m_window;

    bool m_firstMouse = true;

    GLfloat m_lastX = m_width / 2.0;
    GLfloat m_lastY = m_height / 2.0;

    std::string m_title;
    int m_width;
    int m_height;
    bool m_fullScreen;

public:
    GLFWManager(std::string title, int width, int height, bool fullScreen);
    inline ~GLFWManager() { destroy(); };

    // This initialized the window and creates the OpenGL context
    virtual int initialize() override;

    // This swaps the backbuffer to the front and should be called every frame
    virtual void swapBuffers() override;

    // This processes any needed input for the application
    virtual void processInput() override;

    virtual void clear() override;

    // This destroys the window and OpenGL context
    virtual void destroy();

    virtual inline std::string getTitle() const { return m_title; };
    virtual inline int getWidth() const { return m_width; };
    virtual inline int getHeight() const { return m_height; };
    virtual inline float getWindowRatio() const { return float(m_width) / float(m_height); };
    virtual inline bool isFullScreen() const { return m_fullScreen; };

    // Add a way to access and get the application's window
    // virtual inline GLFWwindow *getWindow() const { return m_window; }
};

#endif /* _GLFWManager_HPP_ */