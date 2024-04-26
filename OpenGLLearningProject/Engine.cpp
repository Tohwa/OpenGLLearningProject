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

#pragma region Skybox
    SShader skyboxShaderProgram = SShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");

    std::string skyboxTexture = "../Skybox/universe.jpg";
#pragma endregion

#pragma region Cube
    SShader sunShaderProgram = SShader("LitVertex.glsl", "LitFragment.glsl");

    std::string testTexture = "../Skybox/top.jpg"; 
    std::vector<SVertex> sunVertices =
    {   //		position				color				  normals			  uv
		//											Topside
    { { -0.5f,  0.5f,-0.5f}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
    { { -0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
    { {  0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
    { {  0.5f,  0.5f,-0.5f}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
        //										 Frontface													 
    { { -0.5f,  0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
    { { -0.5f, -0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
    { {  0.5f, -0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
    { {  0.5f,  0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
        //										 Rightface													 
    { {  0.5f,  0.5f, 0.5f}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
    { {  0.5f, -0.5f, 0.5f}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    { {  0.5f, -0.5f,-0.5f}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
    { {  0.5f,  0.5f,-0.5f}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
        //										 Backface
    { {  0.5f,  0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} },
    { {  0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} },
    { { -0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} },
    { { -0.5f,  0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} },
        //										  Leftface
    { { -0.5f,  0.5f,-0.5f}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
    { { -0.5f, -0.5f,-0.5f}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    { { -0.5f, -0.5f, 0.5f}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
    { { -0.5f,  0.5f, 0.5f}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
        //										BottomFace
    { { -0.5f, -0.5f, 0.5f}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} },
    { { -0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} },
    { {  0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
    { {  0.5f, -0.5f, 0.5f}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
    };

    std::vector<unsigned int> sunIndices{};

    for (size_t i = 0; i < 6; i++)
    {
        sunIndices.push_back(0 + i * 4);
        sunIndices.push_back(1 + i * 4);
        sunIndices.push_back(2 + i * 4);
        sunIndices.push_back(0 + i * 4);
        sunIndices.push_back(2 + i * 4);
        sunIndices.push_back(3 + i * 4);
    }

#pragma endregion


    Camera camera{};
    camera.Initialize();

    Light light{};
    light.Initialize(&sunShaderProgram);

    Material sunMaterial{};
    sunMaterial.Initialize(&sunShaderProgram, testTexture);

    Material skyboxMaterial{};
    skyboxMaterial.Initialize(&skyboxShaderProgram, skyboxTexture);

    Mesh sun{glm::vec3(0.0f, 0.0f, 0.0f)}; //CW || 1X
    //Mesh merkur{glm::vec3(2.0f, 0.0f, 0.0f)};    CW | CW || 0.055X
    //Mesh venus{glm::vec3(4.0f, 0.0f, 0.0f)};     CCW(Achsenrotation) | CW(Sonnenrotation) || 0.815X
    Mesh earth(glm::vec3(6.0f, 0.0f, 0.0f)); // CW | CW || 0.85X
    //Mesh mars{glm::vec3(8.0f, 0.0f, 0.0f)};      CW | CW || 0.11X
    //Mesh jupiter{glm::vec3(10.0f, 0.0f, 0.0f)};   CW | CW || 11.2X
    //Mesh saturn{glm::vec3(12.0f, 0.0f, 0.0f)};    CW | CW || 9.45X
    //Mesh uranus{glm::vec3(14.0f, 0.0f, 0.0f)};    CCW(Achsenrotation) | CW(Sonnenrotation) || 4X
    //Mesh neptun{glm::vec3(16.0f, 0.0f, 0.0f)};    CW | CW || 3.88X
    
    sun.Initialize(&sunShaderProgram, "Obj.file", sunVertices/* kann raus sobald obj.file vorhanden sind*/, sunIndices/* kann raus sobald obj.file vorhanden sind*/, false);
    earth.Initialize(&sunShaderProgram, "Obj.file", sunVertices, sunIndices, true);
    


    Skybox skybox{};
    skybox.Initialize(&skyboxShaderProgram);



    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        Time::Update();

        m_Viewport.Update();
        camera.Update();
        sun.Update();
        earth.Update();

        m_Viewport.Draw();
        //skybox.Draw(camera);
        light.Draw();
        sunMaterial.Draw();
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
