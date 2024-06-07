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
#include "BlurFrameBuffer.h"
#include "QuadView.h"

int SEngine::Initialize(void)
{
	if (!glfwInit()) {
		return -1;
	}

	m_Viewport.Initialize();

	glfwSetInputMode(m_Viewport.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Input::Initialize(m_Viewport.GetWindow());
	Time::Initialize();

	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE); // integriertes Anti Alising

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

	BlurFrameBuffer blurFrameBuffer{ 1280, 720 };
	blurFrameBuffer.Initialize();

	QuadView quadView{};

	Camera camera{};
	camera.Initialize();

	GameObject sun{ "sun", glm::vec3(0,0,0) };
	sun.Initialize(textures.sunTextures, "Planet", "Sun");

	GameObject mercury{ "mercury",  glm::vec3(5,0,0) };
	mercury.Initialize(textures.mercuryTextures, "Planet", "Planet");

	GameObject venus{ "venus", glm::vec3(0,0,10) };
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

	GameObject neptune{ "neptune",  glm::vec3(0,0,-40) };
	neptune.Initialize(textures.neptuneTextures, "Planet", "Planet");

	Skybox skybox{};
	skybox.Initialize();

#pragma region Framebuffer Shader
	SShader postShader("PostProcessingVertex.glsl", "PostProcessingFragment.glsl");
	
	postShader.Use();
	unsigned int sceneTex = glGetUniformLocation(postShader.id, "processingTexture");
	glUniform1i(sceneTex, 0);
#pragma endregion

#pragma region Blurshader Setup
	SShader blurShader("BlurVertex.glsl", "BlurFragment.glsl");

	blurShader.Use();
	unsigned int blurTex = glGetUniformLocation(blurShader.id, "blurTexture");
	glUniform1i(blurTex, 0);

	const char* attributeName = "_UVs";
	unsigned int attributeID = blurShader.GetAttributeLocation(attributeName);
	glVertexAttribPointer(attributeID, 2, GL_FLOAT, false, (sizeof(float) * 4), (void*)(sizeof(float) * 2));

	bool horizontal = true, first_iteration = true;
	int amount = 10;
#pragma endregion

#pragma region Blendshader Setup
	SShader blendShader("BlendVertex.glsl", "BlendFragment.glsl");

	blendShader.Use();
	unsigned int hdrTex = glGetUniformLocation(blendShader.id, "hdrTex");
	glUniform1i(hdrTex, 0);

	unsigned int bloomTex = glGetUniformLocation(blendShader.id, "blurTex");
	glUniform1i(bloomTex, 1);

#pragma endregion

	quadView.CreateQuadBuffer(postShader);

	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	while (!glfwWindowShouldClose(m_Viewport.GetWindow())) {

		glEnable(GL_DEPTH_TEST);

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
		glNamedFramebufferDrawBuffers(framebuffer.m_framebufferID, 2, attachments);
		

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


		postShader.Use();
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, framebuffer.m_colBuffers[0]);
		quadView.RenderQuad();

		horizontal = true;
		first_iteration = true;
		amount = 20;

		blurShader.Use();
		for (unsigned int i = 0; i < amount; i++)
		{
			blurFrameBuffer.BindFrameBuffer(GL_FRAMEBUFFER, horizontal);
			blurShader.SetInt("horizontal", horizontal);
			blurFrameBuffer.BindTexture(first_iteration, horizontal, &framebuffer.m_colBuffers[1]);
			quadView.RenderQuad();


			horizontal = !horizontal;

			if (first_iteration)
			{
				first_iteration = false;
			}
		}

		blurFrameBuffer.UnbindFrameBuffer(GL_FRAMEBUFFER);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		blendShader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, framebuffer.m_colBuffers[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, blurFrameBuffer.m_blurColBuffers[!horizontal]);

		quadView.RenderQuad();




		m_Viewport.LateDraw();

		glfwPollEvents();
	}

	framebuffer.Finalize();

	return 0;
}

void SEngine::Finalize(void)
{
}
