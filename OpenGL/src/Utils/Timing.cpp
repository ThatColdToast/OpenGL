#include "Utils/Timing.h"

#include <iostream>

Timer::Timer()
{
    std::cout << "Creating Timer" << std::endl;
    m_old_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());

    m_frameNumber = 0;
    m_sFactor = 50;

    m_deltaTime = 0.0;
    m_deltaTimeSmooth = 0.0;

    m_frameRate = 0.0;
    m_frameRateSmooth = 0.0;
};

Timer::Timer(unsigned int smoothFactor)
{
    std::cout << "Creating Timer" << std::endl;
    m_old_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());

    m_frameNumber = 0;
    m_sFactor = smoothFactor;

    m_deltaTime = 0.0;
    m_deltaTimeSmooth = 0.0;

    m_frameRate = 0.0;
    m_frameRateSmooth = 0.0;
};

void Timer::UpdateTime()
{
    m_frameNumber++;
    
    unsigned long max = 0;
    max--;
    // std::cout << max << std::endl;
    if(m_frameNumber >= max) std::cerr << "Error: (Timing.cpp) frameNumber Overflow" << std::endl;

    m_new_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
    m_deltaTime = (m_new_time.count() - m_old_time.count()) / 1000.0;
    m_old_time = m_new_time;
    m_deltaTimeSmooth = ((m_deltaTimeSmooth * (m_sFactor-1)) + m_deltaTime) / m_sFactor;

    m_frameRate = (1000.0 / m_deltaTime);
    m_frameRateSmooth = (1000.0 / m_deltaTimeSmooth);
};

double Timer::deltaTime()
{
    return m_deltaTime;
};

double Timer::deltaTimeSmooth()
{
    return m_deltaTimeSmooth;
};

double Timer::frameRate()
{
    return m_frameRate;
};

double Timer::frameRateSmooth()
{
    return m_frameRateSmooth;
};

unsigned long Timer::frameNumber()
{
    return m_frameNumber;
};