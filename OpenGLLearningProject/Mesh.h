#ifndef MESH_H
#define MESH_H

#include "IEngineObject.h"
#include "Vertex.h"
#include "Shader.h"
#include "Buffer.h"
#include <vector>

struct Mesh : IEngineObject {

	std::vector<SVertex> vertices{};
	std::vector<unsigned int> indices{};

	SShader* shader{};
	//material

	void Init(SShader* _shader);

	// Geerbt über IEngineObject
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Finalize() override;

private:
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};
	int m_uniform{};
};

#endif // !MESH_H
