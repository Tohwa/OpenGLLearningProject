#include "Viewport.h"
#include <iostream>

// Initializes the viewport by creating a window and setting up OpenGL context
int SViewport::Initialize(void)
{
    // Set OpenGL version and profile settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, M_I_GLFW_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, M_I_GLFW_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 16); // Enable 16x MSAA (Multi-Sample Anti-Aliasing)

    // Create a windowed mode window and its OpenGL context
    m_pWindow = glfwCreateWindow(M_I_WINDOW_WIDTH, M_I_WINDOW_HEIGHT, M_S_TITLE, NULL, NULL);

    // Check if the window creation was successful
    if (!m_pWindow) {
        std::cout << "ERROR: Window creation failed!" << std::endl; // Print error message
        glfwTerminate(); // Terminate GLFW
        return -2; // Return error code indicating window creation failure
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_pWindow);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: GLAD INIT FAILED!" << std::endl; // Print error message
        return -3; // Return error code indicating GLAD initialization failure
    }

    return 0; // Return 0 to indicate successful initialization
}

// Updates the viewport. Currently, it does not perform any operations.
int SViewport::Update(void)
{
    return 0; // Return 0 to indicate that there are no updates
}

// Clears the screen with a dark gray color and clears the depth buffer
int SViewport::Draw(void)
{
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f); // Set the clear color to dark gray with slight transparency
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
    return 0; // Return 0 to indicate successful drawing
}

// Swaps the front and back buffers to display the rendered image
int SViewport::LateDraw(void)
{
    glfwSwapBuffers(m_pWindow); // Swap the front and back buffers to show the new frame

    return 0; // Return 0 to indicate successful buffer swap
}

// Finalizes the viewport. Currently, it does not perform any operations.
void SViewport::Finalize(void)
{
}