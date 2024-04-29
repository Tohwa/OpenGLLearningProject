#ifndef IMATERIAL_H
#define IMATERIAL_H

#include "IComponent.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include <GLM/glm.hpp>
#include <string>
#include <vector>

struct IMaterial : public IComponent
{
	virtual const int Initialize(GameObject& _gameObject) override = 0;
	void InitShader(SShader* _shader, std::vector<std::string> _textures);
	virtual const int Update() override = 0;
	virtual const int Draw() override = 0;
	virtual void Finalize() override = 0;

	glm::vec3 ambient{};
	glm::vec3 diffuse{};
	glm::vec3 specular{};
	float shininess{};

	SShader m_shader{};
	Texture m_texture{};
	unsigned int m_matAmbiID{}, m_matDiffID{}, m_matSpecID{}, m_matShinyID{};
};

#endif // !IMATERIAL_H
