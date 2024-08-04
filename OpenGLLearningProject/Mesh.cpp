#include "Mesh.h"
#include "GameObject.h"

// Constructor for Mesh class, initializes with a Transform object
Mesh::Mesh(Transform& _transform) : m_transform(_transform)
{
	position = _transform.position;
}

/// <summary>
/// Initialize method for Mesh class
/// </summary>
/// <param name="_gameObject"> reference to the GameObject this mesh belongs to </param>
/// <returns></returns>
const int Mesh::Initialize(GameObject& _gameObject)
{
	// Load the model using ObjLoader
	ObjLoader loader("../Obj/planet.obj");
	loader.ReadFile();

	// Generate vertices and indices from the loaded model
	vertices = loader.GenerateVertices();
	indices = loader.indices;

	// Set shader and name from the GameObject
	shader = _gameObject.m_shader;
	m_name = _gameObject.m_name;

	// Create buffers for the mesh
	CreateBuffers();

	// Get uniform locations from the shader
	m_modelID = glGetUniformLocation(shader->id, "model");
	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_normID = glGetUniformLocation(shader->id, "normal");
	m_camPosID = glGetUniformLocation(shader->id, "cameraPosition");

	// Initialize and set the model matrix
	m_transform.InitModelMatrix();
	model = m_transform.GetModelMatrix();
	normal = glm::inverse(glm::mat3(model));

	return 0;
}

// Update method for Mesh class, updates the transformation based on the object's name
const int Mesh::Update()
{
	// Rotate specific objects differently
	if (m_name == "venus" || m_name == "uranus")
	{
		m_transform.Rotate(-0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else
	{
		m_transform.Rotate(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Rotate globally for all objects except "sun"
	if (m_name != "sun")
	{
		m_transform.RotateGlobal(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	// Update model matrix and normal matrix
	model = m_transform.GetModelMatrix();
	normal = glm::inverse(glm::mat3(model));
	return 0;
}

// Draw method for rendering the mesh
// _camera: reference to the camera object for view and projection matrices
const int Mesh::Draw(const Camera& _camera)
{
	// Set the shader uniforms for model, view, projection, normal matrices, and camera position
	glUniformMatrix4fv(m_modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &_camera.view[0][0]);
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]);
	glUniformMatrix3fv(m_normID, 1, GL_TRUE, &normal[0][0]);
	glUniform3fv(m_camPosID, 1, &(_camera.position.x));

	// Bind the vertex array object and draw the elements
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	return 0;
}

// Finalize method for Mesh class, placeholder for cleanup
void Mesh::Finalize()
{
	// Placeholder for any cleanup operations
}

// CreateBuffers method for setting up OpenGL buffers and attributes
void Mesh::CreateBuffers()
{
	// Generate and bind a vertex array object
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Create and fill the vertex buffer object
	m_vertexBuffer.CreateBufferObject();
	m_vertexBuffer.Bind(GL_ARRAY_BUFFER);
	m_vertexBuffer.BufferFill(sizeof(SVertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

	// Set up vertex attributes for position
	const char* attributeName = "_pos";
	unsigned int attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), 0);

	// Set up vertex attributes for color
	attributeName = "_col";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(4, GL_FLOAT, false, sizeof(SVertex), (void*)sizeof(glm::vec3));

	// Set up vertex attributes for normal
	attributeName = "_nor";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));

	// Set up vertex attributes for UV coordinates
	attributeName = "_uv";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuffer.SetAttributeID(attributeName, attributeID);
	m_vertexBuffer.LinkAttribute(2, GL_FLOAT, false, sizeof(SVertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec3)));

	// Create and fill the index buffer object
	m_indexBuffer.CreateBufferObject();
	m_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	// Unbind the vertex array object
	glBindVertexArray(0);
}
