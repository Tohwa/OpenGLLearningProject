#include "Engine.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Light.h"
#include "Material.h"
#include "Input.h"
#include "Time.h"
#include "GameObject.h"
#include "TextureHolder.h"

int SEngine::Initialize(void)
{
    if (!glfwInit()) {
        return -1;
    }

    m_Viewport.Initialize();

    glfwSetInputMode(m_Viewport.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Input::Initialize(m_Viewport.GetWindow());
    Time::Initialize();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);
    
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    return 0;   
}

int SEngine::Run(void)
{
    TextureHolder textures{};

    Camera camera{};
    camera.Initialize();

    GameObject sun{glm::vec3(0,0,0)};
    sun.Initialize(textures.sunTextures, "Lit", "Lit");

    GameObject mercury{ glm::vec3(4,0,0) };
    mercury.Initialize(textures.mercuryTextures, "Lit", "Mercury");

    GameObject venus{glm::vec3(8,0,0)};
    venus.Initialize(textures.venusTextures, "Lit", "Venus");

    GameObject earth{ glm::vec3(12,0,0) };
    earth.Initialize(textures.earthTextures, "Lit", "Earth");
    
    GameObject mars{ glm::vec3(16,0,0) };
    mars.Initialize(textures.marsTextures, "Lit", "Mars");

    GameObject jupiter{ glm::vec3(20,0,0) };
    jupiter.Initialize(textures.jupiterTextures, "Lit", "Jupiter");

    GameObject saturn{ glm::vec3(24,0,0) };
    saturn.Initialize(textures.saturnTextures, "Lit", "Saturn");
    
    GameObject uranus{ glm::vec3(28,0,0) };
    uranus.Initialize(textures.uranusTextures, "Lit", "Uranus");

    GameObject neptune{ glm::vec3(32,0,0) };
    neptune.Initialize(textures.neptuneTextures, "Lit", "Neptun");

    Skybox skybox{};
    skybox.Initialize();



    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        Time::Update();

        m_Viewport.Update();
        camera.Update();
        sun.Update();
        mercury.Update();
        venus.Update();
        earth.Update();
        mars.Update();
        jupiter.Update();
        saturn.Update();
        uranus.Update();
        neptune.Update();


        m_Viewport.Draw();
        sun.Draw(camera);
        mercury.Draw(camera);
        venus.Draw(camera);
        earth.Draw(camera);
        mars.Draw(camera);
        jupiter.Draw(camera);
        saturn.Draw(camera);
        uranus.Draw(camera);
        neptune.Draw(camera);


        skybox.Draw(camera);
        m_Viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
