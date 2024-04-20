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

	/*std::vector<glm::vec3> vertices{};
	std::vector<glm::vec3> normals{};
	std::vector<glm::vec2> uvs{};*/

	std::vector<unsigned int> indices{};

	SShader* shader{};
	//material

	// Geerbt über IEngineObject
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

	glm::vec3 position{0.0f, 0.0f, 0.0f};
	glm::vec3 scale{};
	glm::vec3 rotation{};

	glm::mat4 model{};
	glm::mat3 normal{};

private:
	void CreateBuffers();
	SBuffer m_vertexBuffer{}, m_indexBuffer{};
	unsigned int m_vao{};
	
	unsigned int m_modelID{}, m_viewID{}, m_projID{}, m_normID{}, m_camPosID{};

};

#endif // !MESH_H
