#include "Engine.h"
#include "Mesh.h"
#include "Light.h"
#include "Material.h"

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
    SShader shaderProgram = SShader("LitVertex.glsl", "LitFragment.glsl");
    
    Camera camera{};
    camera.Initialize();

    Light light{};
    light.Initialize(&shaderProgram);

    Material material{};
    material.Initialize(&shaderProgram);
    
    Mesh mesh{};
    mesh.Initialize(&shaderProgram);


    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        m_Viewport.Update();
        mesh.Update();

        m_Viewport.Draw();
        light.Draw();
        material.Draw();
        mesh.Draw(camera);

        m_Viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
