#ifndef SUNMESH_H
#define SUNMES_H

#include "IComponent.h"
#include "Vertex.h"
#include "ObjLoader.h"
#include "Shader.h"
#include "Material.h"
#include "Buffer.h"
#include "Camera.h"
#include <GLM/glm.hpp>
#include <vector>

struct SunMesh : IComponent
{

	// Geerbt über IComponent
	SunMesh(glm::vec3 _position);
	const int Initialize(GameObject& _gameObject) override;
	const int Update() override;
	const int Draw() override;
	void Finalize() override;


private:
	glm::vec3 position;

	std::vector<SVertex> vertices{};

	std::vector<unsigned int> indices{};

	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};

	unsigned int m_modelID{}, m_viewID{}, m_projID{}, m_normID{}, m_camPosID{};

};


#endif // !SUNMESH_H


