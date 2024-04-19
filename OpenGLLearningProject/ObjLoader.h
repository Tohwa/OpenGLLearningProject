#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLM/glm.hpp>

struct ObjLoader
{
	ObjLoader(const std::string& filePath);

	std::string path;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec3> out_normals;
	std::vector<glm::vec2> out_uvs;

	void ReadFile();
};

#endif // !OBJLOADER_H
