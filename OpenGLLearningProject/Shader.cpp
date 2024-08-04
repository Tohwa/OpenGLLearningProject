#include "Shader.h"

/// <summary>
/// Constructor for SShader, takes paths for vertex and fragment shader files
/// </summary>
/// <param name="vertexPath"> path to vertex shader file </param>
/// <param name="fragPath"> path to fragment shader file </param>
SShader::SShader(const char* vertexPath, const char* fragPath) {
	std::string vertexCode{};
	std::string fragmentCode{};
	std::ifstream vertShaderFile{};
	std::ifstream fragShaderFile{};

	// Ensure ifstream objects can throw exceptions
	vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// Open shader files
		vertShaderFile.open(vertexPath);
		fragShaderFile.open(fragPath);

		// Read file buffers into stringstreams
		std::stringstream vertShaderStream;
		std::stringstream fragShaderStream;

		vertShaderStream << vertShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		// Close file handlers
		vertShaderFile.close();
		fragShaderFile.close();

		// Convert stringstreams into strings
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

	// Compile vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR: Vertex Shader Compile Failed!" << std::endl
			<< infoLog << std::endl;
	}

	// Compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment Shader Compile Failed!" << std::endl
			<< infoLog << std::endl;
	}

	// Create shader program and link shaders
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

	// Clean up shaders as they're linked into the program now and no longer needed
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

/// <summary>
/// Constructor for SShader, takes path for fragment shader file
/// </summary>
/// <param name="fragPath"> path to fragment shader file</param>
SShader::SShader(const char* fragPath)
{
	std::string fragmentCode{};
	std::ifstream fragShaderFile{};

	// Ensure ifstream object can throw exceptions
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// Open shader file
		fragShaderFile.open(fragPath);

		// Read file buffer into stringstream
		std::stringstream fragShaderStream;
		fragShaderStream << fragShaderFile.rdbuf();

		// Close file handler
		fragShaderFile.close();

		// Convert stringstream into string
		fragmentCode = fragShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR: Shaderfile was not read!" << std::endl;
	}

	const char* fShaderCode = fragmentCode.c_str();

	unsigned int fragment{};
	int success{};

	char infoLog[512]{};

	// Compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment Shader Compile Failed!" << std::endl
			<< infoLog << std::endl;
	}

	// Create shader program and link shader
	id = glCreateProgram();
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Link Failed!" << std::endl
			<< infoLog << std::endl;
	}

	// Clean up shader as it's linked into the program now and no longer needed
	glDeleteShader(fragment);
}

/// <summary>
/// Set an integer uniform in the shader
/// </summary>
/// <param name="name"> id of the unifor to be set </param>
/// <param name="value"> value to set </param>
void SShader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

// Use the shader program
void SShader::Use()
{
	glUseProgram(id);
}

// Get the location of an attribute in the shader
unsigned int SShader::GetAttributeLocation(const char* _name)
{
	return glGetAttribLocation(id, _name);
}
