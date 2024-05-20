#ifndef MESH_H
#define MESH_H

#include "IComponent.h"
#include "Transform.h"

struct Mesh : IComponent
{

	std::vector<SVertex> vertices{};

	std::vector<unsigned int> indices{};

	SShader* shader{};

	Mesh(Transform& _transform);

	const int Initialize(GameObject& _gameObject) override;

	const int Update() override;

	const int Draw(const Camera& _camera) override;

	void Finalize() override;

	glm::vec3 position{};
	glm::vec3 scale{};
	glm::vec3 rotation{};
	glm::vec3 orbitRotation{};

	glm::mat4 model{};
	glm::mat3 normal{};

	float angle = 0.0f;

	bool canOrbit{};

private:
	std::string m_name{};

	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};

	Transform& m_transform;

	unsigned int m_modelID{}, m_viewID{}, m_projID{}, m_normID{}, m_camPosID{};
};

#endif // !MESH_H
