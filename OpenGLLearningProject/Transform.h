#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "IComponent.h"

struct Transform : IComponent{
	glm::vec3 position{};
	glm::vec3 rotation{};
	glm::vec3 scale{};

	//Transform();
	Transform(glm::vec3 _position);
	const int Initialize(GameObject& _gameObject) override;
	const int Update() override;
	const int Draw(const Camera& _camera) override;
	void Finalize() override;

};

#endif
