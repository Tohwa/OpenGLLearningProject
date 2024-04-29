#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IEngineObject.h"
#include "Transform.h"
#include <vector>
#include "IComponent.h"

struct GameObject : public IEngineObject {

	GameObject() {};

	inline Transform& GetTransform() {
		return transform;
	}

	template <class T>
	T* GetComponent();



	// Geerbt über IEngineObject
	void Initialize(std::string textures[]) override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Finalize() override;

	void AddComponent(IComponent* _component);
	void DeleteComponent(IComponent* _component);

	SShader GetShaderData();
	void GetRenderData();

	SShader* m_shader{};
private:
	Transform transform;
	std::vector<IComponent*> m_Components{};



};

template <class T>
inline T* GameObject::GetComponent() {
	static_assert(std::is_base_of<IComponent, T*>, "No Component!");
	for (IComponent* component : m_Components) {
		auto temp = dynamic_cast<T*>(component);
		if (temp != NULL) {
			return temp;
		}
	}

	return NULL;
}

#endif // !GAMEOBJECT_H
