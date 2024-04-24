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
    

    Mesh sun{glm::vec3(0.0f, 0.0f, 0.0f)}; //CW || 1X
    //Merkur    CW | CW || 0.055X
    //Venus     CCW(Achsenrotation) | CW(Sonnenrotation) || 0.815X
    Mesh earth(glm::vec3(5.0f, 0.0f, 0.0f)); // CW | CW || 0.85X
    //Mars      CW | CW || 0.11X
    //Jupiter   CW | CW || 11.2X
    //Saturn    CW | CW || 9.45X
    //Uranus    CCW(Achsenrotation) | CW(Sonnenrotation) || 4X
    //Neptun    CW | CW || 3.88X
    
    sun.Initialize(&shaderProgram);
    earth.Initialize(&shaderProgram);
    


    Skybox skybox{};
    skybox.Initialize(&skyboxProgram);



    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        Time::Update();

        m_Viewport.Update();
        camera.Update();
        sun.Update();
        earth.Update();

        m_Viewport.Draw();
        light.Draw();
        material.Draw();
        skybox.Draw(camera);
        sun.Draw(camera);
        earth.Draw(camera);

        m_Viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
