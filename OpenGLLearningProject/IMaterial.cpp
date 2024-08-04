#include "IMaterial.h"

const int IMaterial::Initialize(GameObject& _gameObject)
{
	return 0;
}


/// <summary>
/// InitShader method for setting up the shader and textures used by the material.
/// </summary>
/// <param name="_shader"> pointer to the shader object </param>
/// <param name="_textures"> vector of texture filenames </param>
void IMaterial::InitShader(SShader* _shader, std::vector<std::string> _textures)
{
	m_shader = _shader;
	textures = _textures;

	light.Initialize(m_shader);

	// Get the uniform locations for material properties in the shader
	m_matAmbiID = glGetUniformLocation(m_shader->id, "material.ambient");
	m_matDiffID = glGetUniformLocation(m_shader->id, "material.diffuse");
	m_matSpecID = glGetUniformLocation(m_shader->id, "material.specular");
	m_matShinyID = glGetUniformLocation(m_shader->id, "material.shininess");

	m_diffTexture.Initialize(textures[0], m_shader, samplerTextures[0].c_str(), 0);
	
	// If more than one texture is provided, initialize the overlay texture
	if (textures.size() > 1)
	{
		m_overlayTexture.Initialize(_textures[1], m_shader, samplerTextures[1].c_str(), 1);
	}
	// Placeholder for third texture unit initialization (if more than two textures are provided)
	else if (textures.size() > 2) 
	{
		//3rd texUnit
	}
	// Placeholder for fourth texture unit initialization (if more than three textures are provided)
	else if (textures.size() > 3)
	{
		//4th texUnit
	}
}

const int IMaterial::Update()
{
	return 0;
}

/// <summary>
/// Draw method for rendering the material using the given camera.
/// </summary>
/// <param name="_camera"> reference to the Camera object </param>
/// <returns></returns>
const int IMaterial::Draw(const Camera& _camera)
{
	m_shader->Use();

	m_diffTexture.Draw();
	
	// If more than one texture is provided, draw the overlay textur
	if (textures.size() > 1) {
		m_overlayTexture.Draw();
	}
	// Placeholder for drawing the third texture unit (if more than two textures are provided)
	else if (textures.size() > 2)
	{
		//3rd texUnit Draw
	}
	// Placeholder for drawing the fourth texture unit (if more than three textures are provided)
	else if (textures.size() > 3)
	{
		//4th texUnit Draw
	}

	light.Draw();

	// Set the uniform values for the material properties in the shader
	glUniform3fv(m_matAmbiID, 1, &ambient.x);
	glUniform3fv(m_matDiffID, 1, &diffuse.x);
	glUniform3fv(m_matSpecID, 1, &specular.x);
	glUniform3fv(m_matShinyID, 1, &shininess);

	return 0;
}

void IMaterial::Finalize()
{
}
