#include "GameObject.h"

GameObject::GameObject(glm::vec3 _position) : transform(_position), mesh(transform) 
{
	transform.Initialize(*this);
	AddComponent(&transform);
}

void GameObject::Initialize(std::vector<std::string> _textures, const char* _vertPath, const char* _fragPath)
{
	const char* vertexEnding = "Vertex.glsl";
	const char* fragEnding = "Fragment.glsl";
	
	std::string vertexPath = std::string(_vertPath) + vertexEnding;
	std::string fragmentPath = std::string(_fragPath) + fragEnding;

	shader = SShader(vertexPath.c_str(), fragmentPath.c_str());
	
	m_shader = &shader;

	Light light{};
	light.Initialize(&shader);

	material.Initialize(*this);
	material.InitShader(&shader, _textures);

	mesh.Initialize(*this);

	AddComponent(&material);
	AddComponent(&mesh);
}

void GameObject::Update()
{
	transform.Update();
	material.Update();
	mesh.Update();
}

void GameObject::LateUpdate()
{
}

void GameObject::Draw(Camera& _camera)
{
	transform.Draw(_camera);
	material.Draw(_camera);
	mesh.Draw(_camera);
}


void GameObject::AddComponent(IComponent* _component)
{
	if (!_component) return;
	
	m_Components.push_back(_component);
}

void GameObject::DeleteComponent(IComponent* _component)
{
	if (!_component) return;

	for (int i = 0; i < m_Components.size(); i++) {
		if (m_Components[i] == _component) {
			m_Components.erase(m_Components.begin() + i);
			break;
		}
	}
}

SShader GameObject::GetShaderData()
{
	return *m_shader;
}

//not sure if i want this tbh
void GameObject::GetRenderData()
{

}



void GameObject::Finalize()
{
}

