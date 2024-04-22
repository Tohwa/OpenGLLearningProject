#include "Engine.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Light.h"
#include "Material.h"
#include "Input.h"
#include "Time.h"

int SEngine::Initialize(void)
{
    if (!glfwInit()) {
        return -1;
    }

    m_Viewport.Initialize();

    glfwSetInputMode(m_Viewport.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Input::Initialize(m_Viewport.GetWindow());
    Time::Initialize();

    return 0;   
}

int SEngine::Run(void)
{
    SShader shaderProgram = SShader("LitVertex.glsl", "LitFragment.glsl");
    SShader skyboxProgram = SShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
    
    Camera camera{};
    camera.Initialize();

    Light light{};
    light.Initialize(&shaderProgram);

    Material material{};
    material.Initialize(&shaderProgram);
    

    Mesh mesh{};
    mesh.Initialize(&shaderProgram);

    Skybox skybox{};
    skybox.Initialize(&skyboxProgram);



    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        Time::Update();

        m_Viewport.Update();
        camera.Update();
        mesh.Update();

        m_Viewport.Draw();
        skybox.Draw(camera);
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
