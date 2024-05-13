#ifndef LIGHT_H
#define LIGHT_H

#include "IEngineObject.h"
#include <GLM/vec3.hpp>
#include "Shader.h"

struct Light{


	void Initialize(SShader* _shader) ;
	void Draw() ;


	const glm::vec3 position{0.0f, 0.0f, 0.0f};
	const glm::vec3 ambient{0.5f, 0.5f,  0.5f};
	const glm::vec3 diffuse{ 1.0f, 1.0f, 1.0f};
	const glm::vec3 specular{ 1.0f, 1.0f, 1.0f };
	
	float attenuationConst{ 0.01f };
	float attenuationLinear{ 0.1f };
	float attenuationQuad{ 0.001f };

private:
	SShader* m_shader{};
	unsigned int m_posID{}, m_ambientID{}, m_diffID{}, m_specID{};
	unsigned int m_attConst{}, m_attLinear{}, m_attQuad{};
};

#endif // !LIGHT_H