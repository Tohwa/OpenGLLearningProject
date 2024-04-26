#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB_IMAGE/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <STB_IMAGE/stb_image_write.h>

void Texture::Initialize(const std::string& _path, SShader* _shader, const char* _uName, int _unit)
{
	m_shader = _shader;
	m_unit = _unit;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* buffer = stbi_load(_path.c_str(), &m_width, &m_height, &m_bitPerPixel, 4);

	if (buffer) {
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		//glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(buffer);

		m_shader->Use();

		m_texUniform = glGetUniformLocation(m_shader->id, "_uName");
		glUniform1i(m_texUniform, m_unit);
	}
	else {
		std::cout << "Failed to load Texture!" << buffer << std::endl;
		stbi_image_free(buffer);
	}

}

void Texture::Draw()
{
	glActiveTexture(GL_TEXTURE0 + m_unit);
	glBindTexture(GL_TEXTURE_2D, m_id);
}
