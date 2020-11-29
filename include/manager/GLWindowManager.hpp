#pragma once
#ifndef _WindowManager_HPP_
#define _WindowManager_HPP_

#include "InputManager.hpp"
#include "../utils/GLWindowUtils.hpp"

#include <string>
#include <fstream>

namespace manager
{

    /// \class GLWindowManager
    /// \brief Class for managing the creation of the window, input and the
    /// creating of the OpenGL context. This class should be inherited from to create
    /// specific implementations like GLFW or SDL.
    class GLWindowManager
    {
    protected:
        utils::GLWindowUtils *m_windowUtils; /*!< The utilitary class for our window. */

        InputManager *m_inputManager; /*!< The input manager for our window. */

    public:
        /// \brief Destructor. This is needed so that the class inheriting this will have it's deconstructor called.
        virtual ~GLWindowManager() {}

        /// \brief Initialize the window and creates the OpenGL context.
        virtual int initialize() = 0;

        /// \brief Swap the backbuffer to the front (should be called every frame).
        virtual void swapBuffers() = 0;

        /// \brief Process any needed input for the application.
        virtual void processInput() = 0;

        /// \brief Update the window (should be called every frame).
        virtual void update() = 0;

        /// \brief Destroy the window and the OpenGL context.
        virtual void destroy() = 0;

        /// \brief Return the window/application title.
        virtual std::string getTitle() const = 0;
        /// \brief Return the window width.
        virtual int getWidth() const = 0;
        /// \brief Return the window height.
        virtual int getHeight() const = 0;
        /// \brief Return the window ratio (window width divided by window height).
        virtual float getWindowRatio() const = 0;
        /// \brief Return a boolean that indicates whether or not the window is in full screen mode.
        virtual bool isFullScreen() const = 0;

        /// \brief Set the application's InputManager
        /// \param inputManager : A pointer to the inputManager of the application.
        inline void setInputManager(InputManager *inputManager) { m_inputManager = inputManager; };
        /// \brief Return the application's InputManager
        inline InputManager *getInputManager() const { return m_inputManager; };
        /// \brief Set the application's window utility
        /// \param windowUtils : A pointer to the window utility of the application.
        inline void setWindowUtils(utils::GLWindowUtils *windowUtils) { m_windowUtils = windowUtils; };
        /// \brief Return the application's window utility
        inline utils::GLWindowUtils *getWindowUtils() const { return m_windowUtils; };
        // virtual inline auto *getWindow() const = 0;
    };

} // namespace manager

#endif /* _WindowManager_HPP_ */