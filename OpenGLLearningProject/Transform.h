#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <GLM/vec3.hpp>
#include "IComponent.h"

struct Transform : IComponent{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	const int Initialize(GameObject& _gameObject) override;
	const int Update() override;
	const int Draw() override;
	void Finalize() override;

};

#endif
