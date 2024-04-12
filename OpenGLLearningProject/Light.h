#ifndef LIGHT_H
#define LIGHT_H

#include "IEngineObject.h"
#include <GLM/vec3.hpp>
#include "Shader.h"

struct Light : IEngineObject {

	// Geerbt über IEngineObject
	void Initialize() override;
	void Initialize(SShader* _shader) override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Draw(const Camera&) override;
	void Finalize() override;


	const glm::vec3 position{0.0f, 0.0f, 3.0f};
	const glm::vec3 ambient{0.5f, 0.5f,  0.5f};
	const glm::vec3 diffuse{ 0.5f, 0.5f, 0.5f};
	const glm::vec3 specular{ 0.5f, 0.5f, 0.5f};

	float attenuationConst{};
	float attenuationLinear{};
	float attenuationQuad{};

private:
	SShader* m_shader{};
	unsigned int m_posID{}, m_ambientID{}, m_diffID{}, m_specID{};
	unsigned int m_attConst{}, m_attLinear{}, m_attQuad{};
};

#endif // !LIGHT_H