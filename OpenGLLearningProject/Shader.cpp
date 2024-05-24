#include "Shader.h"

SShader::SShader(const char* vertexPath, const char* fragPath){
	std::string vertexCode{};
	std::string fragmentCode{};
	std::ifstream vertShaderFile{};
	std::ifstream fragShaderFile{};

	vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertShaderFile.open(vertexPath);
		fragShaderFile.open(fragPath);

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

	char infoLog[512]{};

	vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR: Vertex Shader Compile Failed!" << std::endl
				<< infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment Shader Compile Failed!" << std::endl
				<< infoLog << std::endl;
	}

	id = glCreateProgram();

	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Link Failed!" << std::endl
				<< infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

SShader::SShader(const char* fragPath)
{

	std::string fragmentCode{};

	std::ifstream fragShaderFile{};

	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {

		fragShaderFile.open(fragPath);

		std::stringstream fragShaderStream;

		fragShaderStream << fragShaderFile.rdbuf();

		fragShaderFile.close();

		fragmentCode = fragShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR: Shaderfile was not read!" << std::endl;
	}

	const char* fShaderCode = fragmentCode.c_str();

	unsigned int fragment{};
	int success{};

	char infoLog[512]{};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment Shader Compile Failed!" << std::endl
			<< infoLog << std::endl;
	}

	id = glCreateProgram();

	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Link Failed!" << std::endl
			<< infoLog << std::endl;
	}

	glDeleteShader(fragment);
}

void SShader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void SShader::Use()
{
	glUseProgram(id);
}

unsigned int SShader::GetAttributeLocation(const char* _name)
{
	return glGetAttribLocation(id, _name);
}
