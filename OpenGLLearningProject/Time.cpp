#include "Time.h"

float Time::m_deltaTime{};
float Time::m_totalTime{};
float Time::m_lastTimeStamp{};


int Time::Initialize()
{
    m_lastTimeStamp = glfwGetTime();
    return 0;
}

void Time::Update()
{
    double now{ glfwGetTime() };
    double diff = now - m_lastTimeStamp;

    m_deltaTime = diff;
    m_totalTime += m_deltaTime;
    m_lastTimeStamp = now;

}
