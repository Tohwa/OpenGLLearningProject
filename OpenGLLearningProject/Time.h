#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

struct Time
{
	static int Initialize();
	inline static float GetDeltaTime() { return m_deltaTime; };
	static void Update();

private:
	static float m_deltaTime;
	static float m_lastTimeStamp;
	static float m_totalTime;

};

#endif // !TIME_H



