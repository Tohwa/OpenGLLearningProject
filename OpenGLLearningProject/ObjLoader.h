#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <GLM/glm.hpp>

struct ObjLoader
{
	unsigned int vertexIndices, uvIndices, normalIndices;

	glm::vec3 temp_vertices;
	glm::vec3 temp_uvs;
	glm::vec3 temp_normals;
};

#endif // !OBJLOADER_H

