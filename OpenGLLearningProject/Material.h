#ifndef MATERIAL_H
#define MATERIAL_H

#include "IEngineObject.h"
#include "Shader.h"
#include <GLM/glm.hpp>

struct Material : IEngineObject {

	// Geerbt �ber IEngineObject
	void Initialize() override;
	void Initialize(SShader* _shader) ;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Draw(const Camera&) ;
	void Finalize() override;


	glm::vec3 ambient{1.0f, 1.0f, 1.0f};
	glm::vec3 diffuse{ 1.0f, 1.0f, 1.0f };
	glm::vec3 specular{ 1.0f, 1.0f, 1.0f };
	float shininess{1.0f};
private:
	SShader* m_shader{};
	unsigned int m_matAmbiID{}, m_matDiffID{}, m_matSpecID{}, m_matShinyID{};
};

#endif // !MATERIAL_H
