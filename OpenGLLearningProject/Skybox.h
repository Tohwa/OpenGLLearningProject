#ifndef SKYBOX_H
#define SKYBOX_H

#include <GLM/glm.hpp>
#include <vector>
#include <string>
#include "Buffer.h"
#include "Shader.h"
#include "Camera.h"

struct Skybox
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	std::string cubeFaces[6] = 
	{
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/RightSide.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/LeftSide.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/TopSide.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/BottomSide.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/FrontSide.jpg",
		"E:/SAE Institute/Repositories/OpenGLLearningProject/Skybox/BackSide.jpg"
	};

	SShader* shader;

	void Initialize(SShader* _shader);
	void Draw(const Camera&);

private:
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};
};

#endif // !SKYBOX_H


