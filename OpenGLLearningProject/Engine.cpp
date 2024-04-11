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

    Light light{};
    light.Init(&shaderProgram);

    Material material{};
    material.Init(&shaderProgram);
    
    Mesh mesh{};
    mesh.Init(&shaderProgram);


    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        m_Viewport.Update();
        mesh.Update();

        m_Viewport.Draw();
        light.Draw();
        material.Draw();
        mesh.DDraw(camera);

        m_Viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
