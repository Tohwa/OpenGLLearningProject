#ifndef ORBITSCRIPT_H
#define ORBITSCRIPT_H

#include "IComponent.h"

class OrbitScript : IComponent
{
	const int Initialize(GameObject& _gameObject) override;
	const int RotateGlobal(float _angle, glm::vec3 _axis);
	const int Update() override;
	const int Draw(const Camera& _camera) override;
	void Finalize() override;
};

#endif // !ORBITSCRIPT_H


