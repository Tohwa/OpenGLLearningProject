#include "Input.h"

GLFWwindow* Input::m_window{};

void Input::Initialize(GLFWwindow* _window)
{
	m_window = _window;
}

bool Input::GetKey(int _key)
{
	if(m_window)
		return glfwGetKey(m_window, _key) == GLFW_PRESS;

	return false;
}

glm::vec2 Input::GetMousePos()
{
	double xpos{};
	double ypos{};

	if (m_window)
		glfwGetCursorPos(m_window, &xpos, &ypos);

	return {xpos, ypos};
}
