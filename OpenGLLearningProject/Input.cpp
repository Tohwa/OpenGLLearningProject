#include "Input.h"

// Static member for storing the GLFW window reference
GLFWwindow* Input::m_window{};

// Initializes the Input class with the given GLFW window
void Input::Initialize(GLFWwindow* _window)
{
    m_window = _window; // Store the window reference for input handling
}

// Checks if a specific key is currently pressed
bool Input::GetKey(int _key)
{
    // If the window is initialized, check the key state
    if (m_window)
        return glfwGetKey(m_window, _key) == GLFW_PRESS; // Return true if the key is pressed

    return false; // Return false if the window is not initialized
}

// Retrieves the current position of the mouse cursor
glm::vec2 Input::GetMousePos()
{
    double xpos{}; // Variable for the mouse x-coordinate
    double ypos{}; // Variable for the mouse y-coordinate

    // If the window is initialized, get the cursor position
    if (m_window)
        glfwGetCursorPos(m_window, &xpos, &ypos); // Store the cursor position in xpos and ypos

    return { xpos, ypos }; // Return the mouse position as a glm::vec2
}
