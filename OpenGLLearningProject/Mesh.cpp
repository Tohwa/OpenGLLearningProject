#include "Mesh.h"
#include <GLFW/glfw3.h>

void Mesh::init(SShader* _shader)
{
	//TODO: add vertex data, add indice vector 

	vertices = {
	//			position				color
		{{-0.5f, -0.5f, 0.0f} , {0.0f, 0.5f, 0.1f,1.0f}},
		{{-0.5f,  0.5f, 0.0f} , {1.0f, 0.5f, 0.1f,1.0f}},
		{{ 0.5f,  0.5f, 0.0f} , {0.5f, 0.5f, 0.1f,1.0f}},
		{{ 0.5f, -0.5f, 0.0f} , {0.0f, 0.5f, 1.0f,1.0f}},
	};

	indices = { 0,1,2,0,2,3 };

	shader = _shader;
	CreateBuffers();
}

void Mesh::Initialize()
{
}

void Mesh::Update()
{
}

void Mesh::LateUpdate()
{
}

void Mesh::Draw()
{
	shader->Use();

	float time = glfwGetTime();
	float value1 = (sin(time) / 2.0f) + 0.5f;
	float value2 = (sin(time * 2) / 0.5f) + 0.5f;

	glUniform4f(m_uniform, value1, 1.0f, value2, 1.0f);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
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

	const char* attributeName = "_color";
	unsigned int attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(4, GL_FLOAT, false, sizeof(SVertex), (void*)sizeof(glm::vec3));

	//offset next attrib
	//(void*)(sizeof(glm::vec3) + sizeof(glm::vec4))

	m_indexBuffer.CreateBufferObject();
	m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	m_uniform = glGetUniformLocation(shader->id, "uniformColor");

	glBindVertexArray(0);

}
