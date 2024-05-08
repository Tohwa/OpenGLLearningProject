#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IEngineObject.h"
#include "Mesh.h"
#include "Transform.h"
#include "IMaterial.h"

struct GameObject : public IEngineObject {

	GameObject(glm::vec3 _position);

	inline Transform& GetTransform() {
		return transform;
	}

	template <class T>
	T* GetComponent();



	// Geerbt über IEngineObject
	void Initialize(std::vector<std::string> _textures, const char* _verPath, const char* _fragPath) override = 0;
	void Update() override = 0;
	void LateUpdate() override = 0;
	void Draw() override = 0;
	void Finalize() override = 0;

	void AddComponent(IComponent* _component);
	void DeleteComponent(IComponent* _component);

	SShader GetShaderData();
	void GetRenderData();

	SShader* m_shader{};
private:
	Transform transform;
	IMaterial material;
	Mesh mesh;
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
