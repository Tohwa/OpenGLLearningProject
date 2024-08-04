#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>

// Initializes the camera's position, direction, and projection matrix
void Camera::Initialize()
{
    // Set initial camera position, direction, and up vector
    position = { 0.0f, 0.0f, 5.0f };
    direction = { 0.0f, 0.0f, -1.0f };
    up = { 0.0f, 1.0f, 0.0f };

    // Create the view matrix using the camera's position, direction, and up vector
    view = glm::lookAt(position, position + direction, up);

    // Create the projection matrix using field of view, aspect ratio, and near/far planes
    projection = glm::perspective(fov, (float)1920 / 1080, nearPlane, farPlane);
}

// Updates the camera's position and direction based on user input and mouse movement
void Camera::Update()
{
    // Move the camera forward if the W key is pressed
    if (Input::GetKey(GLFW_KEY_W)) {
        Translate(direction * 10.0f * Time::GetDeltaTime());
    }
    // Move the camera backward if the S key is pressed
    if (Input::GetKey(GLFW_KEY_S)) {
        Translate(-direction * 10.0f * Time::GetDeltaTime());
    }
    // Move the camera left if the A key is pressed
    if (Input::GetKey(GLFW_KEY_A)) {
        Translate(-glm::normalize(glm::cross(direction, up)) * 10.0f * Time::GetDeltaTime());
    }
    // Move the camera right if the D key is pressed
    if (Input::GetKey(GLFW_KEY_D)) {
        Translate(glm::normalize(glm::cross(direction, up)) * 10.0f * Time::GetDeltaTime());
    }

    // Get the current mouse position
    glm::vec2 newMousePos = Input::GetMousePos();

    // If this is the first mouse movement, initialize last mouse position
    if (m_firstMouse) {
        m_lastMousePos = newMousePos;
        m_firstMouse = false;
    }

    // Calculate the offset between the new and last mouse positions
    float xoffset{ newMousePos.x - m_lastMousePos.x };
    float yoffset{ m_lastMousePos.y - newMousePos.y };

    // Update the last mouse position
    m_lastMousePos = newMousePos;

    // Sensitivity factor for mouse movement
    float sens{ 10.0f * Time::GetDeltaTime() };

    // Apply sensitivity to the mouse offsets
    xoffset *= sens;
    yoffset *= sens;

    // Update yaw and pitch based on mouse movement
    yaw += xoffset;
    pitch += yoffset;

    // Clamp pitch to prevent the camera from flipping over
    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    // Calculate the new direction vector based on yaw and pitch
    glm::vec3 dir{};
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    // Update the camera direction and normalize it
    direction = glm::normalize(dir);

    // Update the view matrix with the new position and direction
    view = glm::lookAt(position, position + direction, up);
}

// Moves the camera by a specified direction vector
void Camera::Translate(glm::vec3 _dir)
{
    position += _dir; // Update the camera's position
}