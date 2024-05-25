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

#pragma region Screen FrameBuffer Setup

#pragma region Framebuffer Shader

	SShader postShader("PostProcessingVertex.glsl", "PostProcessingFragment.glsl");

#pragma endregion

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

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, &quad, GL_STATIC_DRAW); // <- HIER WAR DER FEHLER! frameVAO genutzt...

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

#pragma region Scene Texture

	postShader.Use();
	unsigned int sceneTex = glGetUniformLocation(postShader.id, "processingTexture");
	glUniform1i(sceneTex, 0);


#pragma endregion

#pragma endregion

#pragma region hdrFrameBuffer

	unsigned int hdrFBO{};
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

	unsigned int colorBuffers[2];
	glGenTextures(2, colorBuffers);

	for (int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, framebuffer.width, framebuffer.height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}

#pragma endregion


#pragma region Blur Framebuffer Setup

	SShader blurShader("BlurVertex.glsl", "BlurFragment.glsl");

	unsigned int blurFBO[2];
	unsigned int blurColBuffer[2];
	glGenFramebuffers(2, blurFBO);
	glGenTextures(2, blurColBuffer);

	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[i]);
		glBindTexture(GL_TEXTURE_2D, blurColBuffer[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1280, 720, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurColBuffer[i], 0);
	}

	blurShader.Use();
	unsigned int blurTex = glGetUniformLocation(blurShader.id, "blurTexture");
	glUniform1i(blurTex, 0);

	attributeName = "_UVs";
	attributeID = blurShader.GetAttributeLocation(attributeName);
	glVertexAttribPointer(attributeID, 2, GL_FLOAT, false, (sizeof(float) * 4), (void*)(sizeof(float) * 2));

	bool horizontal = true, first_iteration = true;
	int amount = 10;

#pragma endregion

#pragma region BlendShader

	SShader blendShader("BlendVertex.glsl", "BlendFragment.glsl");

	blendShader.Use();
	unsigned int hdrTex = glGetUniformLocation(blendShader.id, "hdrTex");
	glUniform1i(hdrTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, framebuffer.m_colBuffers);

	unsigned int bloomTex = glGetUniformLocation(blendShader.id, "blurTex");
	glUniform1i(bloomTex, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, blurColBuffer[!horizontal]);

	attributeName = "_UVs";
	attributeID = blendShader.GetAttributeLocation(attributeName);
	glVertexAttribPointer(attributeID, 2, GL_FLOAT, false, (sizeof(float) * 4), (void*)(sizeof(float) * 2));

#pragma endregion

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

		glNamedFramebufferDrawBuffers(hdrFBO, 2, attachments);
		//glDrawBuffers(2, attachments);

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
		glBindTexture(GL_TEXTURE_2D, framebuffer.m_colBuffers);
		glBindVertexArray(frameVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);//worst case uncomment here and you have the solar system without bloom
		glBindVertexArray(0);

		/*glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[0]);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, framebuffer.m_colBuffers[1]);*/

		horizontal = true, first_iteration = true;
		amount = 10;

		blurShader.Use();
		for (unsigned int i = 0; i < amount; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[horizontal]);
			blurShader.SetInt("horizontal", horizontal);

			glActiveTexture(GL_TEXTURE0);
			/*    blurColBuffer[0]   */
			glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : blurColBuffer[!horizontal]);
			glBindVertexArray(frameVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);


			horizontal = !horizontal;

			if (first_iteration)
			{
				first_iteration = false;
			}
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		blendShader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, framebuffer.m_colBuffers);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, blurColBuffer[!horizontal]);

		glBindVertexArray(frameVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);




		m_Viewport.LateDraw();

		glfwPollEvents();
	}

	framebuffer.Finalize();

	return 0;
}

void SEngine::Finalize(void)
{
}
