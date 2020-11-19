#pragma once
#ifndef _WindowManager_HPP_
#define _WindowManager_HPP_

#include "InputManager.hpp"

#include <string>
#include <fstream>

// This is our class definition for managing the creation of the window, input and the
// creating of the OpenGL context.  This class should be inherited from to create
// specific implementations like GLFW (i.e. GLFWManager), Win32, GLUT or SDL.
class WindowManager
{
protected:
    // We created a variable to store an InputManager
    InputManager *m_inputManager;

public:
    // This is needed so that the class inheriting this will have it's deconstructor called
    virtual ~WindowManager() {}

    // This initialized the window and creates the OpenGL context
    virtual int initialize() = 0;

    // This swaps the backbuffer to the front and should be called every frame
    virtual void swapBuffers() = 0;

    // This processes any needed input for the application
    virtual void processInput() = 0;

    // This destroys the window and OpenGL context
    virtual void destroy() = 0;

    // Add a way to access and get the application's InputManager for camera movements
    virtual inline void *setInputManager(InputManager *inputManager) { m_inputManager = inputManager; }
    virtual inline InputManager *getInputManager() const { return m_inputManager; }
};

#endif /* _WindowManager_HPP_ */