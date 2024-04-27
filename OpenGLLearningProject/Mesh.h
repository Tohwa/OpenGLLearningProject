#ifndef MESH_H
#define MESH_H

#include "IEngineObject.h"
#include "Vertex.h"
#include "ObjLoader.h"
#include "Shader.h"
#include "Material.h"
#include "Buffer.h"
#include "Camera.h"
#include <GLM/glm.hpp>
#include <vector>

struct Mesh : IEngineObject {

	std::vector<SVertex> vertices{};

	std::vector<unsigned int> indices{};

	SShader* shader{};
	//material

	Mesh(glm::vec3 _position);

	// Geerbt über IEngineObject
	void Initialize() override;
	void Initialize(SShader* _shader, std::string _path, bool _canOrbit);
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Draw(const Camera&);
	void Finalize() override;

	void Translate(float, float, float);
	void Rotate(float, glm::vec3);
	void Scale(float, float, float);
	void Orbit(float _radius, glm::vec3 _axis);

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
