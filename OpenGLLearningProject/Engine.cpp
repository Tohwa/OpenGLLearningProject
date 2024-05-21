#include "Engine.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Light.h"
#include "Material.h"
#include "Input.h"
#include "Time.h"
#include "GameObject.h"
#include "TextureHolder.h"
#include "FrameBuffer.h"

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
    FrameBuffer framebuffer{1280, 720};

    Camera camera{};
    camera.Initialize();

    GameObject sun{ "sun", glm::vec3(0,0,0)};
    sun.Initialize(textures.sunTextures, "Lit", "Lit");

    GameObject mercury{ "mercury",  glm::vec3(5,0,0) };
    mercury.Initialize(textures.mercuryTextures, "Lit", "Mercury");

    GameObject venus{ "venus", glm::vec3(0,0,10)};
    venus.Initialize(textures.venusTextures, "Lit", "Venus");

    GameObject earth{ "earth",  glm::vec3(-15,0,0) };
    earth.Initialize(textures.earthTextures, "Lit", "Earth");
    
    GameObject mars{ "mars",  glm::vec3(0,0,-20) };
    mars.Initialize(textures.marsTextures, "Lit", "Mars");

    GameObject jupiter{ "jupiter", glm::vec3(25,0,0) };
    jupiter.Initialize(textures.jupiterTextures, "Lit", "Jupiter");

    GameObject saturn{ "saturn",  glm::vec3(0,0,30) };
    saturn.Initialize(textures.saturnTextures, "Lit", "Saturn");
    
    GameObject uranus{ "uranus",  glm::vec3(-35,0,0) };
    uranus.Initialize(textures.uranusTextures, "Lit", "Uranus");

    GameObject neptune{ "neputne",  glm::vec3(0,0,-40) };
    neptune.Initialize(textures.neptuneTextures, "Lit", "Neptun");

    Skybox skybox{};
    skybox.Initialize();



    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        framebuffer.BindFrameBuffer(GL_FRAMEBUFFER);

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

        framebuffer.UnbindFrameBuffer(GL_FRAMEBUFFER);
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
