#pragma once

#include <chrono>

class Timer
{
private:
    std::chrono::microseconds m_old_time;
    std::chrono::microseconds m_new_time;

    double m_deltaTime;
    double m_deltaTimeSmooth;

    double m_frameRate;
    double m_frameRateSmooth;

    unsigned int m_sFactor;
    unsigned int m_frameNumber;

public:
    Timer();
    Timer(unsigned int smoothFactor);

    void UpdateTime();

    double deltaTime();
    double deltaTimeSmooth();

    double frameRate();
    double frameRateSmooth();

    unsigned long frameNumber();
};