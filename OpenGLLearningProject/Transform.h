#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "IComponent.h"

struct GameObject;

struct Transform : IComponent{
	glm::vec3 position{};
	glm::vec3 rotation{};
	glm::vec3 scale{};

	Transform(glm::vec3 _position);

	const int Initialize(GameObject& _gameObject) override;
	const int Translate(float _x, float _y, float _z);
	const int Rotate(float _angle, glm::vec3 _axis);
	const int Scale(float _x, float _y, float _z);
	const int Update() override;
	const int Draw(const Camera& _camera) override;
	void Finalize() override;

	void InitModelMatrix();
	glm::mat4 GetModelMatrix() const;

private:
	glm::mat4 modelMatrix{ 1.0f };
};

#endif //!TRANSFORM_H
