#include "Mesh.h"
#include <GLFW/glfw3.h>
#include <GLM/gtx/transform.hpp>

void Mesh::Initialize()
{
}

void Mesh::Initialize(SShader* _shader)
{
	vertices = {
		//			position				color
		//					    Topside
			{{ -0.5f,  0.5f,-0.5f}, {0.0f, 1.0f, 0.1f,1.0f}},
			{{ -0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 0.1f,1.0f}},
			{{  0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 0.1f,1.0f}},
			{{  0.5f,  0.5f,-0.5f}, {0.0f, 1.0f, 0.1f,1.0f}},
		//					   Frontface
			{{ -0.5f,  0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}},
			{{ -0.5f, -0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}},
			{{  0.5f, -0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}},
			{{  0.5f,  0.5f, 0.5f}, {0.7f, 1.0f, 0.1f,1.0f}},
		//					   Rightface
			{{  0.5f,  0.5f, 0.5f}, {0.0f, 0.5f, 0.5f,1.0f}},
			{{  0.5f, -0.5f, 0.5f}, {0.0f, 0.5f, 0.5f,1.0f}},
			{{  0.5f, -0.5f,-0.5f}, {0.0f, 0.5f, 0.5f,1.0f}},
			{{  0.5f,  0.5f,-0.5f}, {0.0f, 0.5f, 0.5f,1.0f}},
		//					   Backface
			{{  0.5f,  0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}},
			{{  0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}},
			{{ -0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}},
			{{ -0.5f,  0.5f,-0.5f}, {1.0f, 0.5f, 0.5f,1.0f}},
		//					     Leftface
			{{ -0.5f,  0.5f,-0.5f}, {0.7f, 0.2f, 0.5f,1.0f}},
			{{ -0.5f, -0.5f,-0.5f}, {0.7f, 0.2f, 0.5f,1.0f}},
			{{ -0.5f, -0.5f, 0.5f}, {0.7f, 0.2f, 0.5f,1.0f}},
			{{ -0.5f,  0.5f, 0.5f}, {0.7f, 0.2f, 0.5f,1.0f}},
		//						BottomFace
			{{ -0.5f, -0.5f, 0.5f}, {1.0f, 0.5f, 1.0f,1.0f}},
			{{ -0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 1.0f,1.0f}},
			{{  0.5f, -0.5f,-0.5f}, {1.0f, 0.5f, 1.0f,1.0f}},
			{{  0.5f, -0.5f, 0.5f}, {1.0f, 0.5f, 1.0f,1.0f}},
	};

	indices = { 
			  0,1,2,0,2,3,			//topface
			  4,5,6,4,6,7,			//frontface
			  8,9,10,8,10,11,		//rightface
			  12,13,14,12,14,15,	//backface
			  16,17,18,16,18,19,	//leftface
			  20,21,22,20,22,23		//bottomface
	};

	/*ObjLoader loader("E:/SAE Institute/Repositories/OpenGLLearningProject/Obj/IcoSphere.obj");

	loader.ReadFile();

	vertices = loader.temp_vertices;

	indices = loader.vertexIndices;*/

	/*for (int i = 0; i < loader.temp_vertices.size(); i++) {
		vertices.push_back(loader.temp_vertices[i]);
	}

	for (int i = 0; i < loader.vertexIndices.size(); i++) {
		indices.push_back(loader.vertexIndices[i]);
	}*/

	shader = _shader;
	CreateBuffers();

	m_modelID = glGetUniformLocation(shader->id, "model");
	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_normID = glGetUniformLocation(shader->id, "normal");

	model = glm::translate(glm::mat4(1.0), position);
	normal = glm::inverse(glm::mat3(model));


}

void Mesh::Update()
{
	/*Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	Rotate(0.03f, glm::vec3(0.1f, 0.0f, 0.0f));
	Rotate(0.01f, glm::vec3(0.0f, 0.0f, 1.0f));*/
}

void Mesh::LateUpdate()
{
}

void Mesh::Draw()
{
}

void Mesh::Draw(const Camera& _camera)
{
	shader->Use();

	glUniformMatrix4fv(m_modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &_camera.view[0][0]);
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);
	glUniformMatrix4fv(m_normID, 1, GL_FALSE, &normal[0][0]);

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

	//offset next attrib
	//(void*)(sizeof(glm::vec3) + sizeof(glm::vec4))

	m_indexBuffer.CreateBufferObject();
	m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);

}
