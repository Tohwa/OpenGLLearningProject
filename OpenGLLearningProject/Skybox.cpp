#include "Skybox.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB_IMAGE/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <STB_IMAGE/stb_image_write.h>

void Skybox::Initialize(SShader* _shader)
{
	vertices =
	{
		{ -1.0, -1.0,  1.0},
		{  1.0, -1.0,  1.0},
		{  1.0, -1.0, -1.0},
		{ -1.0, -1.0, -1.0},
		{ -1.0,  1.0,  1.0},
		{  1.0,  1.0,  1.0},
		{  1.0,  1.0, -1.0},
		{ -1.0,  1.0, -1.0},
	};

	indices = 
	{
		1,2,6,
		6,5,1,

		0,4,7,
		7,3,2,

		4,5,6,
		6,7,4,

		0,3,2,
		2,1,0,

		0,1,5,
		5,4,0,

		3,7,6,
		6,2,3
	};

	shader = _shader;
	CreateBuffers();

	glGenTextures(1, &cubeMapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; i++) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(cubeFaces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load Texture!" << cubeFaces[i] << std::endl;
			stbi_image_free(data);
		}

	}

	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_skyID = glGetUniformLocation(shader->id, "skybox");
}

void Skybox::Draw(const Camera& _camera)
{
	glDepthFunc(GL_LEQUAL);

	shader->Use();

	glUniform1i(m_skyID, 0);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	view = glm::mat4(glm::mat3(_camera.view));
	projection = _camera.projection;

	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);

	glBindVertexArray(m_vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glDepthFunc(GL_LESS);
}


void Skybox::CreateBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vertexBuffer.CreateBufferObject();
	m_vertexBuffer.Bind(GL_ARRAY_BUFFER);
	m_vertexBuffer.BufferFill(sizeof(vertices) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

	const char* attributeName = "_pos";
	unsigned int attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(3, GL_FLOAT, false, sizeof(glm::vec3), 0);

	m_indexBuffer.CreateBufferObject();
	m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
