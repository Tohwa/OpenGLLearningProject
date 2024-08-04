#include "Time.h"

// Initialize static member variables
float Time::m_deltaTime{};
float Time::m_totalTime{};
float Time::m_lastTimeStamp{};

// Initializes the Time class by setting the initial timestamp
int Time::Initialize()
{
    m_lastTimeStamp = glfwGetTime(); // Store the current time as the last timestamp
    return 0; // Return 0 to indicate successful initialization
}

// Updates time-related values. Call this method each frame.
void Time::Update()
{
    double now = glfwGetTime(); // Get the current time
    double diff = now - m_lastTimeStamp; // Calculate the time difference since the last update

    m_deltaTime = diff; // Store the time difference as delta time
    m_totalTime += m_deltaTime; // Accumulate the total time
    m_lastTimeStamp = now; // Update the last timestamp to the current time
}