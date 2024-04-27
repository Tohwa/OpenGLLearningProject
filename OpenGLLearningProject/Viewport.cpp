#include "Viewport.h"
#include <iostream>

int SViewport::Initialize(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, M_I_GLFW_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, M_I_GLFW_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_pWindow = glfwCreateWindow(M_I_WINDOW_WIDTH, M_I_WINDOW_HEIGHT, M_S_TITLE, NULL, NULL);

    if (!m_pWindow) {

        std::cout << "ERROR: Window creation failed!" << std::endl;
        glfwTerminate();
        return -2; //ERROR: Window creation failed!
    }

    glfwMakeContextCurrent(m_pWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: GLAD INIT FAILED!" << std::endl;
        return -3;
    }




    return 0;
}

int SViewport::Update(void)
{
    return 0;
}

int SViewport::Draw(void)
{
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return 0;
}

int SViewport::LateDraw(void)
{
    glfwSwapBuffers(m_pWindow);

    return 0;
}

void SViewport::Finalize(void)
{
}
