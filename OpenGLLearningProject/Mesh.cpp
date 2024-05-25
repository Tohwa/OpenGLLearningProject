#include "Mesh.h"
#include "GameObject.h"

Mesh::Mesh(Transform& _transform) : m_transform(_transform)
{
	position = _transform.position;
}

const int Mesh::Initialize(GameObject& _gameObject)
{

	ObjLoader loader("../Obj/IcoSphere.obj");

	loader.ReadFile();

	vertices = loader.GenerateVertices();
	indices = loader.indices;

	shader = _gameObject.m_shader;
	m_name = _gameObject.m_name;

	CreateBuffers();

	m_modelID = glGetUniformLocation(shader->id, "model");
	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_normID = glGetUniformLocation(shader->id, "normal");
	m_camPosID = glGetUniformLocation(shader->id, "cameraPosition");

	m_transform.InitModelMatrix();
	model = m_transform.GetModelMatrix();
	normal = glm::inverse(glm::mat3(model));

	return 0;
}

const int Mesh::Update()
{
	if (m_name == "venus" || m_name == "uranus")
	{
		m_transform.Rotate(-0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else
	{
		m_transform.Rotate(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (m_name != "sun")
	{
		m_transform.RotateGlobal(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	model = m_transform.GetModelMatrix();
	normal = glm::inverse(glm::mat3(model));
	return 0;
}

const int Mesh::Draw(const Camera& _camera)
{
	glUniformMatrix4fv(m_modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &_camera.view[0][0]);
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);
	glUniformMatrix3fv(m_normID, 1, GL_TRUE, &normal[0][0]);
	glUniform3fv(m_camPosID, 1, &(_camera.position.x));

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	return 0;
}

void Mesh::Finalize()
{

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
