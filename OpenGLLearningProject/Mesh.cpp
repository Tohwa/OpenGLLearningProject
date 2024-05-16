#include "Mesh.h"
#include "GameObject.h"

//Mesh::Mesh()
//{
//}

Mesh::Mesh(Transform& _transform)
{
	position = _transform.position;
}

//void Mesh::Initialize(SShader* _shader, std::string _path, bool _canOrbit)
//{
//	/*canOrbit = _canOrbit;
//	vertices = _vertices;
//
//	indices = _indices;*/
//	//ObjLoader loader(_path);
//	ObjLoader loader("../Obj/IcoSphere.obj");
//
//	loader.ReadFile();
//
//	vertices = loader.finalVertices;
//	indices = loader.GenerateIndices(loader.out_vertices, loader.out_normals, loader.out_uvs, loader.indices);
//
//	shader = _shader;
//	CreateBuffers();
//
//	m_modelID = glGetUniformLocation(shader->id, "model");
//	m_viewID = glGetUniformLocation(shader->id, "view");
//	m_projID = glGetUniformLocation(shader->id, "projection");
//	m_normID = glGetUniformLocation(shader->id, "normal");
//	m_camPosID = glGetUniformLocation(shader->id, "cameraPosition");
//
//	model = glm::translate(glm::mat4(1.0), position);
//	normal = glm::inverse(glm::mat3(model));
//
//	
//}

//void Mesh::Update()
//{
//	//Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
//	//Rotate(0.03f, glm::vec3(0.1f, 0.0f, 0.0f));
//	//Rotate(0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
//
//	//if (canOrbit)
//	//{
//	//	angle += 0.001f; // Ändere den Winkel für die Rotation
//	//	if (angle > 2 * glm::pi<float>())
//	//	{
//	//		angle -= 2 * glm::pi<float>(); // Winkel nicht über 360 Grad halten
//	//	}
//
//	//	Orbit(position.x, glm::vec3(0.0f, 1.0f, 0.0f));
//	//}
//}

//void Mesh::Draw(const Camera& _camera)
//{
//	//shader->Use();
//
//	glUniformMatrix4fv(m_modelID, 1, GL_FALSE, &model[0][0]);
//	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &_camera.view[0][0]);
//	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);
//	glUniformMatrix3fv(m_normID, 1, GL_TRUE, &normal[0][0]);
//	glUniform3fv(m_camPosID, 1, &(_camera.position.x));
//
//	glBindVertexArray(m_vao);
//	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//}



const int Mesh::Initialize(GameObject& _gameObject)
{

	ObjLoader loader("../Obj/IcoSphere.obj");

	loader.ReadFile();

	vertices = loader.GenerateVertices();;
	indices = loader.indices;

	shader = _gameObject.m_shader;
	
	CreateBuffers();

	m_modelID = glGetUniformLocation(shader->id, "model");
	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_normID = glGetUniformLocation(shader->id, "normal");
	m_camPosID = glGetUniformLocation(shader->id, "cameraPosition");

	model = glm::translate(glm::mat4(1.0), position);
	normal = glm::inverse(glm::mat3(model));

	return 0;
}

const int Mesh::Update()
{
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
