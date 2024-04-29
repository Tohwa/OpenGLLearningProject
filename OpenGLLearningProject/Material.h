#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "Texture.h"
#include <GLM/glm.hpp>

struct Material{

	void Initialize(SShader* _shader, std::string _path) ;
	void Draw();

	glm::vec3 ambient{1.0f, 1.0f, 1.0f};
	glm::vec3 diffuse{ 0.2f, 0.3f, 0.0f };
	glm::vec3 specular{ 0.2f, 0.1f, 0.5f };
	float shininess{32.0f};
private:
	SShader* m_shader{};
	Texture m_texture{};
	unsigned int m_matAmbiID{}, m_matDiffID{}, m_matSpecID{}, m_matShinyID{};
};

#endif // !MATERIAL_H
