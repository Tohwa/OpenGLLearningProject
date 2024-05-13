#include "IMaterial.h"

const int IMaterial::Initialize(GameObject& _gameObject)
{
	return 0;
}

void IMaterial::InitShader(SShader* _shader, std::vector<std::string> _textures)
{
	m_shader = _shader;

	light.Initialize(m_shader);

	m_matAmbiID = glGetUniformLocation(m_shader->id, "material.ambient");
	m_matDiffID = glGetUniformLocation(m_shader->id, "material.diffuse");
	m_matSpecID = glGetUniformLocation(m_shader->id, "material.specular");
	m_matShinyID = glGetUniformLocation(m_shader->id, "material.shininess");

	int i{};
	for (const std::string& path : _textures) 
	{
		m_texture.Initialize(path, m_shader, "diffuseTexture", i);

		i++;
	}
	

	//TODO: FInd a way to change diffusetexture to another during for each loop
}

const int IMaterial::Update()
{
	return 0;
}

const int IMaterial::Draw(const Camera& _camera)
{
	m_shader->Use();

	m_texture.Draw();

	light.Draw();

	glUniform3fv(m_matAmbiID, 1, &ambient.x);
	glUniform3fv(m_matDiffID, 1, &diffuse.x);
	glUniform3fv(m_matSpecID, 1, &specular.x);
	glUniform3fv(m_matShinyID, 1, &shininess);

	return 0;
}

void IMaterial::Finalize()
{
}
