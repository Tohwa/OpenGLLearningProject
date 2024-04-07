#include "Engine.h"

int SEngine::Initialize(void)
{
    if (!glfwInit()) {
        return -1;
    }

    m_Viewport.Initialize();

    return 0;   
}

int SEngine::Run(void)
{
    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        //TODO: Additional Updates and Draws for Elements 

        m_Viewport.Update();
        m_Viewport.Draw();

        glfwPollEvents();
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
