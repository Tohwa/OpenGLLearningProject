#include "Engine.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Light.h"
#include "Material.h"
#include "Input.h"
#include "Time.h"
#include "GameObject.h"

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

#pragma region Skybox
    std::string skyboxTexture = "../Skybox/universe.jpg";
#pragma endregion

    SShader sunShader = SShader("LitVertex.glsl", "LitFragment.glsl");
    SShader mercuryShader = SShader("MercuryVertex.glsl", "MercuryFragment.glsl");
    SShader venusShader = SShader("VenusVertex.glsl", "VenusFragment.glsl");
    SShader earthShader = SShader("EarthVertex.glsl", "EarthFragment.glsl");
    SShader marsShader = SShader("marsVertex.glsl", "marsFragment.glsl");
    SShader jupiterShader = SShader("jupiterVertex.glsl", "jupiterFragment.glsl");
    SShader saturnShader = SShader("saturnVertex.glsl", "saturnFragment.glsl");
    SShader uranusShader = SShader("uranusVertex.glsl", "uranusFragment.glsl");
    SShader neptunShader = SShader("neptunVertex.glsl", "neptunFragment.glsl");
    
    std::string sunTexture = "../Textures/2k_sun.jpg"; 
    std::string mercuryTexture = "../Textures/2k_mercury.jpg";
    std::string venusTexture = "../Textures/2k_venus_surface.jpg";
    std::string earthTexture = "../Textures/2k_earth_daymap.jpg";
    std::string marsTexture = "../Textures/2k_mars.jpg";
    std::string jupiterTexture = "../Textures/2k_jupiter.jpg";
    std::string saturnTexture = "../Textures/2k_saturn.jpg";
    std::string uranusTexture = "../Textures/2k_uranus.jpg";
    std::string neptunTexture = "../Textures/2k_neptune.jpg";

#pragma region Cube

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


    std::vector<std::string> textures
    {
        "../Textures/2k_sun.jpg"
    };

    Camera camera{};
    camera.Initialize();

    GameObject sun{glm::vec3(0,0,0)};
    sun.Initialize(textures, "LitVertex.glsl", "LitFragment.glsl");

    //Light sunlight{};
    //sunlight.Initialize(&sunShader);
    //Light mercuryLight{};
    //mercuryLight.Initialize(&mercuryShader);
    //Light venusLight{};
    //venusLight.Initialize(&venusShader);
    //Light earthLight{};
    //earthLight.Initialize(&earthShader);
    //Light marsLight{};
    //marsLight.Initialize(&marsShader);
    //Light jupiterLight{};
    //jupiterLight.Initialize(&jupiterShader);
    //Light saturnLight{};
    //saturnLight.Initialize(&saturnShader);
    //Light uranusLight{};
    //uranusLight.Initialize(&uranusShader);
    //Light neptunLight{};
    //neptunLight.Initialize(&neptunShader);


    //Material sunMaterial{};
    //sunMaterial.Initialize(&sunShader, sunTexture); 
    //Material mercuryMaterial{};
    //mercuryMaterial.Initialize(&mercuryShader, mercuryTexture);
    //Material venusMaterial{};
    //venusMaterial.Initialize(&venusShader, venusTexture);
    //Material earthMaterial{};
    //earthMaterial.Initialize(&earthShader, earthTexture);
    //Material marsMaterial{};
    //marsMaterial.Initialize(&marsShader, marsTexture);
    //Material jupiterMaterial{};
    //jupiterMaterial.Initialize(&jupiterShader, jupiterTexture);
    //Material saturnMaterial{};
    //saturnMaterial.Initialize(&saturnShader, saturnTexture);
    //Material uranusMaterial{};
    //uranusMaterial.Initialize(&uranusShader, uranusTexture);
    //Material neptunMaterial{};
    //neptunMaterial.Initialize(&neptunShader, neptunTexture);




    //Mesh sun{glm::vec3(0.0f, 0.0f, 0.0f)}; //CW || 1X
    //Mesh mercury{glm::vec3(4.0f, 0.0f, 0.0f)}; //   CW | CW || 0.055X
    //Mesh venus{glm::vec3(8.0f, 0.0f, 0.0f)};   //  CCW(Achsenrotation) | CW(Sonnenrotation) || 0.815X
    //Mesh earth(glm::vec3(12.0f, 0.0f, 0.0f)); // CW | CW || 0.85X
    //Mesh mars{glm::vec3(16.0f, 0.0f, 0.0f)};    //  CW | CW || 0.11X
    //Mesh jupiter{glm::vec3(20.0f, 0.0f, 0.0f)};  // CW | CW || 11.2X
    //Mesh saturn{glm::vec3(24.0f, 0.0f, 0.0f)};   // CW | CW || 9.45X
    //Mesh uranus{glm::vec3(28.0f, 0.0f, 0.0f)};  // CCW(Achsenrotation) | CW(Sonnenrotation) || 4X
    //Mesh neptun{glm::vec3(32.0f, 0.0f, 0.0f)};  //  CW | CW || 3.88X
    //
    //
    //sun.Initialize(&sunShader, "ignore this", false);
    //mercury.Initialize(&mercuryShader, "ignore this", false);
    //venus.Initialize(&venusShader, "ignore this", false);
    //earth.Initialize(&earthShader, "ignore this", false);
    //mars.Initialize(&marsShader, "ignore this", false);
    //jupiter.Initialize(&jupiterShader, "ignore this", false);
    //saturn.Initialize(&saturnShader, "ignore this", false);
    //uranus.Initialize(&uranusShader, "ignore this", false);
    //neptun.Initialize(&neptunShader, "ignore this", false);




    Skybox skybox{};
    skybox.Initialize();



    while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

        Time::Update();

        m_Viewport.Update();
        camera.Update();
        sun.Update();
        /*sun.Update();
        mercury.Update();
        venus.Update();
        earth.Update();
        mars.Update();
        jupiter.Update();
        saturn.Update();
        uranus.Update();
        neptun.Update();*/

        m_Viewport.Draw();
        sun.Draw(camera);
        /*sunlight.Draw();
        sunMaterial.Draw();
        sun.Draw(camera);

        mercuryLight.Draw();
        mercuryMaterial.Draw();
        mercury.Draw(camera);

        venusLight.Draw();
        venusMaterial.Draw();
        venus.Draw(camera);

        earthLight.Draw();
        earthMaterial.Draw();
        earth.Draw(camera);

        marsLight.Draw();
        marsMaterial.Draw();
        mars.Draw(camera);

        jupiterLight.Draw();
        jupiterMaterial.Draw();
        jupiter.Draw(camera);

        saturnLight.Draw();
        saturnMaterial.Draw();
        saturn.Draw(camera);

        uranusLight.Draw();
        uranusMaterial.Draw();
        uranus.Draw(camera);

        neptunLight.Draw();
        neptunMaterial.Draw();
        neptun.Draw(camera);*/

        skybox.Draw(camera);
        m_Viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void SEngine::Finalize(void)
{
}
