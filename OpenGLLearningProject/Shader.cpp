#include "Shader.h"

SShader::SShader(const char* vertexPath, const char* fragPath)
{
	/*TODO: Auslesen der filestreams um die daraus generierten strings
	* zum kompilieren der shader auf der grafikkarte zu nutzen
	*/

	//TODO: Link compiled shader!
}

void SShader::Use()
{
	glUseProgram(id);
}
