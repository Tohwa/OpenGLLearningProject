#include "Material.h"

void Material::Initialize(SShader* _shader, std::string _path)
{
	m_shader = _shader;
	m_matAmbiID = glGetUniformLocation(m_shader->id, "material.ambient");
	m_matDiffID = glGetUniformLocation(m_shader->id, "material.diffuse");
	m_matSpecID = glGetUniformLocation(m_shader->id, "material.specular");
	m_matShinyID = glGetUniformLocation(m_shader->id, "material.shininess");

	m_texture.Initialize(_path, m_shader, "diffuseTexture", 0);
}

void Material::Draw()
{
	//m_shader->Use();

	m_texture.Draw();

	glUniform3fv(m_matAmbiID, 1, &ambient.x);
	glUniform3fv(m_matDiffID, 1, &diffuse.x);
	glUniform3fv(m_matSpecID, 1, &specular.x);
	glUniform3fv(m_matShinyID, 1, &shininess);
}

