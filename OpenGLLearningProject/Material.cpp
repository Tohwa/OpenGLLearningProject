#include "Material.h"

/// <summary>
/// Initialize method for Material class
/// </summary>
/// <param name="_shader"> pointer to the shader object </param>
/// <param name="_path"> path to the texture file </param>
void Material::Initialize(SShader* _shader, std::string _path)
{
	// Assign shader to member variable
	m_shader = _shader;

	// Get the uniform locations for material properties in the shader
	m_matAmbiID = glGetUniformLocation(m_shader->id, "material.ambient");
	m_matDiffID = glGetUniformLocation(m_shader->id, "material.diffuse");
	m_matSpecID = glGetUniformLocation(m_shader->id, "material.specular");
	m_matShinyID = glGetUniformLocation(m_shader->id, "material.shininess");

	// Initialize the texture with the provided path
	m_texture.Initialize(_path, m_shader, "diffuseTexture", 0);
}

// Draw method for rendering the material
void Material::Draw()
{
	// Draw the texture
	m_texture.Draw();

	// Set the uniform values for the material properties in the shader
	glUniform3fv(m_matAmbiID, 1, &ambient.x);
	glUniform3fv(m_matDiffID, 1, &diffuse.x);
	glUniform3fv(m_matSpecID, 1, &specular.x);
	glUniform3fv(m_matShinyID, 1, &shininess);
}

