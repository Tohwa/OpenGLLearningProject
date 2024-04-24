#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include "Buffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Viewport.h"

struct Skybox
{
	std::vector<SVertex> vertices{};
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> uvs;

	glm::vec3 position;

	glm::mat4 model;
	glm::mat4 view;

	//std::string fullFace = "C:/GitRepos/OpenGLLearningProject/Skybox/RightSide.jpg";

	std::string cubeFaces[6] = 
	{
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/left.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/right.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/top.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/bottom.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/back.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/front.jpg"
		
		/*"C:/GitRepos/OpenGLLearningProject/Skybox/left.jpg",
		"C:/GitRepos/OpenGLLearningProject/Skybox/right.jpg",
		"C:/GitRepos/OpenGLLearningProject/Skybox/top.jpg",
		"C:/GitRepos/OpenGLLearningProject/Skybox/bottom.jpg",
		"C:/GitRepos/OpenGLLearningProject/Skybox/back.jpg",
		"C:/GitRepos/OpenGLLearningProject/Skybox/front.jpg"*/
	};

	SShader* shader;

	void Initialize(SShader* _shader);
	void Draw(const Camera& _camera);

private:
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int cubeMapTexture;
	unsigned int m_vao{}, m_viewID{}, m_projID{}, m_modelID{}, m_skyID{};
};

#endif // !SKYBOX_H


