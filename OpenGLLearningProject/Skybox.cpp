#include "Skybox.h"
#include <GLM/gtx/transform.hpp>

void Skybox::Initialize()
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


	shader = SShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	CreateBuffers();


	glGenTextures(1, &cubeMapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
	
	int i{};
	stbi_set_flip_vertically_on_load(false);
	for (const std::string& path:cubeFaces) {
		int width{}, height{}, bitPerPixel{};

		unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bitPerPixel, 0);

		if (buffer) {
			

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
			stbi_image_free(buffer);


		}
		else {
			std::cout << "Failed to load Texture!" << buffer << std::endl;
			stbi_image_free(buffer);
		}
		i++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	shader.Use();

	m_viewID = glGetUniformLocation(shader.id, "view");
	m_projID = glGetUniformLocation(shader.id, "projection");
	m_skyID = glGetUniformLocation(shader.id, "skybox");

	glUniform1i(m_skyID, 0);
	model = glm::translate(glm::mat4(1.0), position);
}

void Skybox::Draw(const Camera& _camera)
{
	GLint currentDepthFunc{};
	glGetIntegerv(GL_DEPTH_FUNC, &currentDepthFunc);
	glDepthFunc(GL_LEQUAL);
	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	view = glm::lookAt(glm::vec3(0.0f), _camera.direction, _camera.up);

	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);

	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glDepthFunc(currentDepthFunc);

}


void Skybox::CreateBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vertexBuffer.CreateBufferObject();
	m_vertexBuffer.Bind(GL_ARRAY_BUFFER);
	m_vertexBuffer.BufferFill(sizeof(SVertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

	const char* attributeName = "_pos";
	unsigned int attributeID = shader.GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), 0);

	m_indexBuffer.CreateBufferObject();
	m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
