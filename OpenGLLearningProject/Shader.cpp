#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

SShader::SShader(const char* vertexPath, const char* fragPath){
	std::string vertexCode{};
	std::string fragmentCode{};
	std::ifstream vertShaderFile{};
	std::ifstream fragShaderFile{};

	vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertShaderFile.open(vertexCode);
		fragShaderFile.open(fragmentCode);

		std::stringstream vertShaderStream;
		std::stringstream fragShaderStream;

		vertShaderStream << vertShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		vertShaderFile.close();
		fragShaderFile.close();

		vertexCode = vertShaderStream.str();
		fragmentCode = fragShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR: Shaderfile was not read!" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex{};
	unsigned int fragment{};
	int success{};

	char infoLog{};

	vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Compile Failed!" << std::endl;
		std::cout << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &vShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Compile Failed!" << std::endl;
		std::cout << infoLog << std::endl;
	}

	id = glCreateProgram();

	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Compile Failed!" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void SShader::Use()
{
	glUseProgram(id);
}

unsigned int SShader::GetAttributeLocation(const char* _name)
{
	return glGetAttribLocation(id, _name);
}
