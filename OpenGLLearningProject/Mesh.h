#ifndef MESH_H
#define MESH_H

#include "IComponent.h"
#include "Transform.h"

struct Mesh : IComponent
{

	std::vector<SVertex> vertices{};

	std::vector<unsigned int> indices{};

	SShader* shader{};
	//material
	//Mesh();
	Mesh(Transform& _transform);

	//void Initialize(SShader* _shader, std::string _path, bool _canOrbit);
	//void Draw(const Camera&);

	/*void Translate(float, float, float);
	void Rotate(float, glm::vec3);
	void Scale(float, float, float);
	void Orbit(float _radius, glm::vec3 _axis);*/
	// Geerbt über IComponent
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
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};
	
	unsigned int m_modelID{}, m_viewID{}, m_projID{}, m_normID{}, m_camPosID{};



};

#endif // !MESH_H
