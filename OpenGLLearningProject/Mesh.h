#ifndef MESH_H
#define MESH_H

#include "IEngineObject.h"
#include "Vertex.h"
#include "Shader.h"
#include "Buffer.h"
#include "Camera.h"
#include <vector>

struct Mesh : IEngineObject {

	std::vector<SVertex> vertices{};
	std::vector<unsigned int> indices{};

	SShader* shader{};
	//material

	void Init(SShader* _shader);
	void DDraw(const& Camera);
	// Geerbt über IEngineObject
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Finalize() override;

	void Translate(float, float, float);
	void Rotate(float, glm::vec3);
	void Scale(float, float, float);

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 model;
	glm::mat3 normal;

private:
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};
	
	unsigned int m_modelID{}, m_viewID{}, m_projID{}, m_normID{};

};

#endif // !MESH_H
