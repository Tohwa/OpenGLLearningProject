#include "Texture.h"

/// <summary>
/// Initialize method for Texture class
/// </summary>
/// <param name="_path"> path to the texture file </param>
/// <param name="_shader"> pointer to the shader object </param>
/// <param name="_uName"> name of the uniform in the shader </param>
/// <param name="_unit"> texture unit to bind to </param>
void Texture::Initialize(const std::string& _path, SShader* _shader, const char* _uName, int _unit)
{
	m_shader = _shader;
	m_unit = _unit;

	// Set the STB image loader to flip images vertically on load
	stbi_set_flip_vertically_on_load(true);

	// Load the texture image data from file
	unsigned char* buffer = stbi_load(_path.c_str(), &m_width, &m_height, &m_bitPerPixel, 4);

	// If the buffer is not empty, proceed with texture creation
	if (buffer) {
		// Generate and bind a texture ID
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		// Load texture data into the bound texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		// Set texture parameters for filtering and wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
		// Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0); 

		// Free the loaded image data as it is now stored in the GPU
		stbi_image_free(buffer);

		// Use the shader program and set the texture uniform
		m_shader->Use();
		m_texUniform = glGetUniformLocation(m_shader->id, _uName);
		glUniform1i(m_texUniform, m_unit);
	}
	else {
		// If the texture failed to load, output an error message
		std::cout << "Failed to load Texture!" << buffer << std::endl;
		stbi_image_free(buffer);
	}

}

// Draw method for binding the texture to its assigned texture unit
void Texture::Draw()
{
	// Activate the appropriate texture unit and bind the texture
	glActiveTexture(GL_TEXTURE0 + m_unit);
	glBindTexture(GL_TEXTURE_2D, m_id);
}
