#include "Mesh.h"
#include <GLFW/glfw3.h>
#include <GLM/gtx/transform.hpp>

Mesh::Mesh(glm::vec3 _position)
{
	position = _position;
}

void Mesh::Initialize()
{
}

void Mesh::Initialize(SShader* _shader, std::string _path, bool _canOrbit)
{
	/*canOrbit = _canOrbit;
	vertices = _vertices;

	indices = _indices;*/
	//ObjLoader loader(_path);
	ObjLoader loader("C:/GitRepos/OpenGLLearningProject/Obj/IcoSphere.obj");

	loader.ReadFile();

	vertices = loader.finalVertices;
	indices = loader.GenerateIndices(loader.out_vertices, loader.out_normals, loader.out_uvs, loader.indices);

	shader = _shader;
	CreateBuffers();

	m_modelID = glGetUniformLocation(shader->id, "model");
	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_normID = glGetUniformLocation(shader->id, "normal");
	m_camPosID = glGetUniformLocation(shader->id, "cameraPosition");

	model = glm::translate(glm::mat4(1.0), position);
	normal = glm::inverse(glm::mat3(model));

	
}

void Mesh::Update()
{
	Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	//Rotate(0.03f, glm::vec3(0.1f, 0.0f, 0.0f));
	//Rotate(0.01f, glm::vec3(0.0f, 0.0f, 1.0f));

	//if (canOrbit)
	//{
	//	angle += 0.001f; // Ändere den Winkel für die Rotation
	//	if (angle > 2 * glm::pi<float>())
	//	{
	//		angle -= 2 * glm::pi<float>(); // Winkel nicht über 360 Grad halten
	//	}

	//	Orbit(position.x, glm::vec3(0.0f, 1.0f, 0.0f));
	//}
}

void Mesh::LateUpdate()
{
}

void Mesh::Draw()
{

}

void Mesh::Draw(const Camera& _camera)
{
	//shader->Use();

	glUniformMatrix4fv(m_modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &_camera.view[0][0]);
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);
	glUniformMatrix3fv(m_normID, 1, GL_TRUE, &normal[0][0]);
	glUniform3fv(m_camPosID, 1, &(_camera.position.x));

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::Finalize()
{

}

void Mesh::Translate(float _x, float _y, float _z)
{
	position += glm::vec3(_x, _y, _z);
	model = glm::translate(model, glm::vec3(_x, _y, _z));
	normal = glm::inverse(glm::mat3(model));
}

void Mesh::Rotate(float _angle, glm::vec3 _axis)
{
	rotation += _axis * _angle;
	model = glm::rotate(model, glm::radians(_angle), _axis);
	normal = glm::inverse(glm::mat3(model));
}

void Mesh::Scale(float _x, float _y, float _z)
{
	model = glm::scale(model, glm::vec3(_x, _y, _z));
}

void Mesh::Orbit(float _radius, glm::vec3 _axis)
{

	float angleInRadians = glm::radians(angle);
	float x = _radius * cos(angleInRadians);
	float z = _radius * sin(angleInRadians);

	model = glm::translate(model, glm::vec3(x, 0.0f, z));
	model = glm::rotate(model, (angle * 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));

}

void Mesh::CreateBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	m_vertexBuffer.CreateBufferObject();
	m_vertexBuffer.Bind(GL_ARRAY_BUFFER);
	m_vertexBuffer.BufferFill(sizeof(SVertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	
	const char* attributeName = "_pos";
	unsigned int attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), 0);

	attributeName = "_col";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(4, GL_FLOAT, false, sizeof(SVertex), (void*)sizeof(glm::vec3));

	attributeName = "_nor";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));

	attributeName = "_uv";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(2, GL_FLOAT, false, sizeof(SVertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec3)));

	m_indexBuffer.CreateBufferObject();
	m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);

}
