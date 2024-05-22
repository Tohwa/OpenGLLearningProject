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
    
    FrameBuffer framebuffer{ 1280, 720 };
    framebuffer.Initialize();
    
    Camera camera{};
    camera.Initialize();

    GameObject sun{ "sun", glm::vec3(0,0,0)};
    sun.Initialize(textures.sunTextures, "Planet", "Planet");

    GameObject mercury{ "mercury",  glm::vec3(5,0,0) };
    mercury.Initialize(textures.mercuryTextures, "Planet", "Planet");

    GameObject venus{ "venus", glm::vec3(0,0,10)};
    venus.Initialize(textures.venusTextures, "Planet", "Planet");

    GameObject earth{ "earth",  glm::vec3(-15,0,0) };
    earth.Initialize(textures.earthTextures, "Planet", "Earth");
    
    GameObject mars{ "mars",  glm::vec3(0,0,-20) };
    mars.Initialize(textures.marsTextures, "Planet", "Planet");

    GameObject jupiter{ "jupiter", glm::vec3(25,0,0) };
    jupiter.Initialize(textures.jupiterTextures, "Planet", "Planet");

    GameObject saturn{ "saturn",  glm::vec3(0,0,30) };
    saturn.Initialize(textures.saturnTextures, "Planet", "Planet");
    
    GameObject uranus{ "uranus",  glm::vec3(-35,0,0) };
    uranus.Initialize(textures.uranusTextures, "Planet", "Planet");

    GameObject neptune{ "neputne",  glm::vec3(0,0,-40) };
    neptune.Initialize(textures.neptuneTextures, "Planet", "Planet");

    Skybox skybox{};
    skybox.Initialize();

#pragma region Framebuffer Shader

    SShader postShader("PostProcesssingVertex.glsl", "PostProcessingFragment.glsl");

#pragma endregion


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

        framebuffer.BindFrameBuffer(GL_FRAMEBUFFER);

#pragma region framebuffer Quad

        float quad[] = {
            -1.0f,1.0f,0.0f,1.0f,
            -1.0f,-1.0f,0.0f,0.0f,
            1.0f,-1.0f,1.0f,0.0f,
            -1.0f,1.0f,0.0f,1.0f,
            1.0f,-1.0f,1.0f,0.0f,
            1.0f,1.0f,1.0f,1.0f
        };

#pragma endregion

#pragma region framebuffer VAO

        unsigned int frameVAO{};
        SBuffer frameVertexBuffer{};

        glGenVertexArrays(1, &frameVAO);
        glBindVertexArray(frameVAO);

        frameVertexBuffer.CreateBufferObject();
        frameVertexBuffer.Bind(GL_ARRAY_BUFFER);
        
        glBufferData(frameVAO, sizeof(float) * 24, &quad, GL_STATIC_DRAW);

        const char* attributeName = "aPos";
        unsigned int attributeID = postShader.GetAttributeLocation(attributeName);
        frameVertexBuffer.SetAttributeID(attributeName, attributeID);
        frameVertexBuffer.LinkAttribute(2, GL_FLOAT, false, sizeof(float) * 4, 0);

        attributeName = "aUVs";
        attributeID = postShader.GetAttributeLocation(attributeName);
        frameVertexBuffer.SetAttributeID(attributeName, attributeID);
        frameVertexBuffer.LinkAttribute(2, GL_FLOAT, false, (sizeof(float) * 4), (void*)(sizeof(float) * 2));

        glBindVertexArray(0);

#pragma endregion


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

        framebuffer.UnbindFrameBuffer(GL_FRAMEBUFFER);

        m_Viewport.LateDraw();

        glfwPollEvents();

    }

    return 0;
}

void SEngine::Finalize(void)
{
}
