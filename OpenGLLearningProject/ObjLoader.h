#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <random>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLM/glm.hpp>
#include "Vertex.h"

struct ObjLoader
{
	ObjLoader(const std::string& filePath);

	std::string path;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::vector<SVertex> finalVertices;
	std::vector<unsigned int> indices;

	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec3> out_normals;
	std::vector<glm::vec2> out_uvs;

	std::unordered_map<std::string, unsigned int> IndexMap;

	//float randomFloat01();

	void ReadFile();

	std::vector<SVertex> GenerateVertices();
	std::vector<unsigned int> GenerateIndices(const std::vector<unsigned int>& vertexIndices, const std::vector<unsigned int>& normalIndices, const std::vector<unsigned int>& uvIndices);

	//std::vector<unsigned int> GenerateIndices(std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<glm::vec2>, std::vector<unsigned int>);
};

#endif // !OBJLOADER_H
