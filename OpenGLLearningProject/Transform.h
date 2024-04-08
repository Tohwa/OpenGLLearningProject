#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <GLM/vec3.hpp>
#include "IEngineObject.h"
struct Transform : IEngineObject{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;



	// Geerbt über IEngineObject
	void Initialize() override;

	void Update() override;

	void LateUpdate() override;

	void Draw() override;

	void Finalize() override;

};

#endif
