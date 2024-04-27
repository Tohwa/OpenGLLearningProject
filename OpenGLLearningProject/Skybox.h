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
#include "stb_image.h"

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
		"../Skybox/redeclipse_right.png",
		"../Skybox/redeclipse_left.png",
		"../Skybox/redeclipse_top.png",
		"../Skybox/redeclipse_down.png",
		"../Skybox/redeclipse_front.png",
		"../Skybox/redeclipse_back.png",
	};

	SShader shader;

	void Initialize();
	void Draw(const Camera& _camera);

private:
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int cubeMapTexture;
	unsigned int m_vao{}, m_viewID{}, m_projID{}, m_skyID{};
};

#endif // !SKYBOX_H


