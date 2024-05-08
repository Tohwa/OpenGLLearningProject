#include "GameObject.h"

GameObject::GameObject(glm::vec3 _position) : transform(_position), mesh(transform){
	transform.Initialize(*this);
	AddComponent(&transform);
}

void GameObject::Initialize(std::vector<std::string> _textures, const char* _vertPath, const char* _fragPath)
{
	SShader shader = SShader(_vertPath, _fragPath);


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

void GameObject::Draw()
{
	//transform.Draw(/*Camera*/);
	//material.Draw(/*Camera*/);
	//mesh.Draw(/*Camera*/);
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

void GameObject::GetRenderData()
{
}

void GameObject::Finalize()
{
}

