#include "Light.h"

void Light::Initialize(SShader* _shader)
{
	m_shader = _shader;

	m_posID = glGetUniformLocation(m_shader->id, "light.position");
	m_ambientID = glGetUniformLocation(m_shader->id, "light.ambient");
	m_diffID = glGetUniformLocation(m_shader->id, "light.diffuse");
	m_specID = glGetUniformLocation(m_shader->id, "light.specular");

	m_attConst = glGetUniformLocation(m_shader->id, "light.attConst");
	m_attLinear = glGetUniformLocation(m_shader->id, "light.attLin");
	m_attQuad = glGetUniformLocation(m_shader->id, "light.attQuad");
}

void Light::Draw()
{
	m_shader->Use();

	glUniform3fv(m_posID, 1, &position.x);
	glUniform3fv(m_ambientID, 1, &ambient.x);
	glUniform3fv(m_diffID, 1, &diffuse.x);
	glUniform3fv(m_specID, 1, &specular.x);

	glUniform1fv(m_attConst, 1, &attenuationConst);
	glUniform1fv(m_attLinear, 1, &attenuationLinear);
	glUniform1fv(m_attQuad, 1, &attenuationQuad);
}
