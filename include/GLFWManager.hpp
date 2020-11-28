#pragma once
#ifndef _GLFWManager_HPP_
#define _GLFWManager_HPP_

#include "GLWindowManager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>

/// \class GLFWManager
/// \brief Class which is the implementation of the abstract base class GLWindowManager, and which uses the
/// GLFW cross-platform library to create a window, handle input and create the OpenGL
/// context.
class GLFWManager : public GLWindowManager
{
protected:
    GLFWwindow *m_window; /*!< The GLFW window object (pointer) that manages the window and input. */

    GLFWmonitor *m_monitor; /*!< The primary monitor of the user, which will be used to displai the application window. */

    bool m_firstMouse = true; /*!< A boolean used to determine if the click captured is the first. */

    GLfloat m_lastX = m_width / 2.0;  /*!< The last position of the mouse X position. */
    GLfloat m_lastY = m_height / 2.0; /*!< The last position of the mouse Y position. */

    std::string m_title; /*!< The window/application title (string). */
    int m_width;         /*!< The window width value. */
    int m_height;        /*!< The window height value. */
    bool m_fullScreen;   /*!< A boolean to determine if the window is in full screen mode. */

public:
    /// \brief Constructor.
    /// \param title : The window/application title.
    /// \param width : The window width value.
    /// \param height : The window height value.
    /// \param fullScreen : A boolean to determine if the window is in full screen mode.
    GLFWManager(std::string title, int width, int height, bool fullScreen);
    /// \brief Destructor.
    inline ~GLFWManager() { destroy(); };

    /// \brief Initialize the window and creates the OpenGL context.
    virtual int initialize() override;

    /// \brief Get information about GLFW and OpenGL contexts.
    void getContext();

    /// \brief Create the GLFW window, either in full screen or not.
    void createWindow();

    /// \brief Center the GLFW window on the monitor screen.
    void centerWindow();

    /// \brief Swap the backbuffer to the front (should be called every frame).
    virtual void swapBuffers() override;

    /// \brief Process any needed input for the application.
    virtual void processInput() override;

    /// \brief Update the window (should be called every frame).
    virtual void update() override;

    /// \brief Destroy the window and the OpenGL context.
    virtual void destroy();

    /// \brief Return the window/application title.
    virtual inline std::string getTitle() const { return m_title; };
    /// \brief Return the window width.
    virtual inline int getWidth() const { return m_width; };
    /// \brief Return the window height.
    virtual inline int getHeight() const { return m_height; };
    /// \brief Return the window ratio (window width divided by window height).
    virtual inline float getWindowRatio() const { return float(m_width) / float(m_height); };
    /// \brief Return a boolean that indicates whether or not the window is in full screen mode.
    virtual inline bool isFullScreen() const { return m_fullScreen; };

    /// \brief Access and get the application's window
    // virtual inline GLFWwindow *getWindow() const { return m_window; }
};

#endif /* _GLFWManager_HPP_ */