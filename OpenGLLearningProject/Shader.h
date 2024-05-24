#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct SShader
{
	unsigned int id{};
	inline SShader() {};
	SShader(const char* vertexPath, const char* fragPath);
	SShader(const char* fragPath);
	void SetInt(const std::string& name, int value);
	void Use();

	unsigned int GetAttributeLocation(const char* _name);
};

#endif

