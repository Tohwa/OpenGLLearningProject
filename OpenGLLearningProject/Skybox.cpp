#include "Skybox.h"

void Skybox::Initialize(SShader* _shader)
{
	vertices = {
		//	   position		        color				  normals			 uv
		////								Frontface													 
		{{ -1,  1, 1}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {0.33f, 1.0f}},
		{{ -1, -1, 1}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {0.66f, 1.0f}},
		{{  1, -1, 1}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {0.66f, 0.75f}},
		{{  1,  1, 1}, {0.7f, 1.0f, 0.1f,1.0f}, {0.0f, 0.0f, 1.0f}, {0.33f, 0.75f}},
		//			1	1					Topside
		{{ -1,  1, 1}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {0.33f, 0.75f}},
		{{  1,  1, 1}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {0.66f, 0.75f}},
		{{  1,  1,-1}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {0.66f, 0.5f}},
		{{ -1,  1,-1}, {0.0f, 1.0f, 0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, {0.33f, 0.5f}},
		//			1	1					Rightface													 
	   {{  1,  1, 1}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {0.66f, 0.75f}},
	   {{  1, -1, 1}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.75f}},
	   {{  1, -1,-1}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.5f}},
	   {{  1,  1,-1}, {0.0f, 0.5f, 0.5f,1.0f}, {1.0f, 0.0f, 0.0f}, {0.66f, 0.5f}},
	   //			1	1					Backface
	   {{  1,  1,-1}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {0.33f, 0.5f}},
	   {{  1, -1,-1}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {0.66f, 0.5f}},
	   {{ -1, -1,-1}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {0.66f, 0.25f}},
	   {{ -1,  1,-1}, {1.0f, 0.5f, 0.5f,1.0f}, {0.0f, 0.0f, -1.0f}, {0.33f, 0.25f}},
	   //			1	1					Leftface
	   {{ -1,  1,-1}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {0.33f, 0.75f}},
	   {{ -1, -1,-1}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.75f}},
	   {{ -1, -1, 1}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.5f}},
	   {{ -1,  1, 1}, {0.7f, 0.2f, 0.5f,1.0f}, {-1.0f, 0.0f, 0.0f}, {0.33f, 0.5f}},
	   //			1	1				  BottomFace
	   {{ -1, -1, 1}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {0.33f, 0.25f}},
	   {{ -1, -1,-1}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {0.66f, 0.25f}},
	   {{  1, -1,-1}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {0.66f, 0.0f}},
	   {{  1, -1, 1}, {1.0f, 0.5f, 1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, {0.33f, 0.0f}}
	};


	for (size_t i = 0; i < 6; i++)
	{
		indices.push_back(0 + i * 4);
		indices.push_back(3 + i * 4);
		indices.push_back(2 + i * 4);
		indices.push_back(0 + i * 4);
		indices.push_back(2 + i * 4);
		indices.push_back(1 + i * 4);
	}
	

	shader = _shader;
	CreateBuffers();

	glGenTextures(1, &cubeMapTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_modelID = glGetUniformLocation(shader->id, "model");
	m_skyID = glGetUniformLocation(shader->id, "skybox");

	model = glm::translate(glm::mat4(1.0), position);
}

void Skybox::Draw(const Camera& _camera)
{
	shader->Use();

	view = glm::mat4(glm::mat3(_camera.view));

	glUniformMatrix4fv(m_modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);
	glUniform1i(m_skyID, 0);

	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}


void Skybox::CreateBuffers()
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

	m_indexBuffer.CreateBufferObject();
	m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
