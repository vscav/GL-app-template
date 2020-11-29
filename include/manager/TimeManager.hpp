#pragma once
#ifndef _TimeManager_HPP
#define _TimeManager_HPP

#include <iostream>
#include <chrono>
#include <thread>

namespace manager
{

    /// \class TimeManager
    /// \brief Class (Singleton) used to manage the time of our main application.
    class TimeManager
    {
    private:
        /// \brief Default constructor.
        TimeManager(){};
        /// \brief Copy constructor.
        TimeManager(TimeManager const &);
        /// \brief Affectation operator.
        TimeManager &operator=(TimeManager const &);

    public:
        /// \brief The function to get the instance of the manager, or initialize and return the instance.
        static TimeManager &getInstance()
        {
            static TimeManager instance;

            return instance;
        }

        /// \brief This calculates our current scene's frames per second and displays it in the console.
        /// \param writeToConsole : A boolean to indicate wheter or not we display the value in the console.
        double calculateFrameRate(bool writeToConsole);

        /// \brief This returns the current time in seconds.
        double getTime();

        /// \brief This pauses the current thread for an amount of time in milliseconds.
        /// \param milliseconds : The duration of sleep in milliseconds.
        void sleep(int milliseconds);

        double deltaTime = 0; /*!< The time slice that stores the total time in seconds that has elapsed since the last frame. */

        double currentTime = 0; /*!< The current time of the manager instance. */
    };

} // namespace manager

#endif /* _TimeManager_HPP */