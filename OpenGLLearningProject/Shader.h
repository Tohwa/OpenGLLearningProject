#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>

struct SShader
{
	unsigned int id{};
	inline SShader() {};
	SShader(const char* vertexPath, const char* fragPath);
	void Use();

	unsigned int GetAttributeLocation(const char* _name);
};

#endif

