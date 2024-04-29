#include "IMaterial.h"

void IMaterial::InitShader(SShader* _shader, std::vector<std::string> _textures)
{
	m_matAmbiID = glGetUniformLocation(_shader->id, "material.ambient");
	m_matDiffID = glGetUniformLocation(_shader->id, "material.diffuse");
	m_matSpecID = glGetUniformLocation(_shader->id, "material.specular");
	m_matShinyID = glGetUniformLocation(_shader->id, "material.shininess");

	int i{};
	for (const std::string& path : _textures) 
	{
		m_texture.Initialize(path, _shader, "diffuseTexture", i);

		i++;
	}
	
	//TODO: FInd a way to change diffusetexture to another during for each loop
}
