#ifndef IMATERIAL_H
#define IMATERIAL_H

#include "IComponent.h"

struct IMaterial : public IComponent
{
	const int Initialize(GameObject& _gameObject) override;
	void InitShader(SShader* _shader, std::vector<std::string> _textures);
	const int Update() override;
	const int Draw(const Camera& _camera) override;
	void Finalize() override;

	glm::vec3 ambient{};
	glm::vec3 diffuse{};
	glm::vec3 specular{};
	float shininess{};

	Light light{};
	SShader* m_shader{};
	Texture m_texture{};
	unsigned int m_matAmbiID{}, m_matDiffID{}, m_matSpecID{}, m_matShinyID{};
};

#endif // !IMATERIAL_H
