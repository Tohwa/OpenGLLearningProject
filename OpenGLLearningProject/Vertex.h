#ifndef VERTEX_H
#define VERTEX_H
#include <GLM/glm.hpp>


struct SVertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
};

#endif
