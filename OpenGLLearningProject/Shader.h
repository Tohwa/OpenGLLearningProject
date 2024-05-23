#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>

struct SShader
{
	unsigned int id{};
	inline SShader() {};
	SShader(const char* vertexPath, const char* fragPath);
	SShader(const char* fragPath);
	void SetInt(const char* _name, bool _bool);
	void Use();

	unsigned int GetAttributeLocation(const char* _name);
};

#endif

