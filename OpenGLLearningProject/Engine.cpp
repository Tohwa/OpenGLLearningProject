#include "Engine.h"
#include "Mesh.h"

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
    SShader shaderProgram = SShader("Vertex.glsl", "Fragment.glsl");
    Mesh mesh{};
    mesh.Init(&shaderProgram);


    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        m_Viewport.Update();
        mesh.Update();

        m_Viewport.Draw();
        mesh.Draw();

        m_Viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
