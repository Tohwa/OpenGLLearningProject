#include "GameObject.h"

void GameObject::Initialize()
{
}

void GameObject::Initialize(SShader*)
{
}

void GameObject::Update()
{
}

void GameObject::LateUpdate()
{
}

void GameObject::Draw()
{
}

void GameObject::Draw(const Camera&)
{
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

void GameObject::Finalize()
{
}

