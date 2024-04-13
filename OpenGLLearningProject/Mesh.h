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

	// Geerbt �ber IEngineObject
	void Initialize() override;
	void Initialize(SShader*);
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Draw(const Camera&);
	void Finalize() override;

	void Translate(float, float, float);
	void Rotate(float, glm::vec3);
	void Scale(float, float, float);

	glm::vec3 position{0.0f};
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 model{1.0f};
	glm::mat3 normal;

private:
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};
	
	unsigned int m_modelID{}, m_viewID{}, m_projID{}, m_normID{};

};

#endif // !MESH_H