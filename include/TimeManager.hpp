#pragma once
#ifndef _TimeManager_HPP
#define _TimeManager_HPP

#include <iostream>
#include <chrono>
#include <thread>

// Singleton class
class TimeManager
{
private:
    TimeManager(){};
    TimeManager(TimeManager const &);
    TimeManager &operator=(TimeManager const &);

public:
    // The function to get the instance of the manager, or initialize and return the instance.
    // By creating a static variable of the instance we ensure this only gets created once.
    // This is also thread-safe in C++ 11 according to the specifications.
    static TimeManager &Instance()
    {
        static TimeManager instance;

        return instance;
    }

    // This calculates our current scene's frames per second and displays it in the console
    double calculateFrameRate(bool writeToConsole);

    // This returns the current time in seconds (since 1/1/1970, call "epoch")
    double getTime();

    // This pauses the current thread for an amount of time in milliseconds
    void sleep(int milliseconds);

    // This is the time slice that stores the total time in seconds that has elapsed since the last frame
    double deltaTime = 0;

    // This is the current time in seconds
    double currentTime = 0;
};

#endif /* _TimeManager_HPP */