#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Shader.h"
#include "stb_image.h"

struct Texture
{
	inline ~Texture() { glDeleteTextures(1, &m_id); m_shader = nullptr; }
	void Initialize(const std::string& _path, SShader* _shader, const char* _uName, int _unit);
	void Draw();

private:
	SShader* m_shader{};
	unsigned int m_id{};
	unsigned int m_texUniform{};
	std::string m_path;
	int m_width{}, m_height{}, m_bitPerPixel{}, m_unit{};
};

#endif // !TEXTURE_H
