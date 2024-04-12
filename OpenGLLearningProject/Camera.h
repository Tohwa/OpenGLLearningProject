#ifndef CAMERA_H
#define CAMERA_H
#include <GLM/glm.hpp>

#include "IEngineObject.h"

struct Camera : IEngineObject
{
	glm::vec3 position{};
	glm::vec3 direction{};
	glm::vec3 up{};

	glm::mat4 view{};
	glm::mat4 projection{};

	float nearPlane{ 0.5f }, farPlane{ 100.0f };
	float fov{ 40.0f };

	// Geerbt �ber IEngineObject
	void Initialize() override;
	void Initialize(SShader* _shader) override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Draw(const Camera&) override;
	void Finalize() override;

	void Translate(float, float, float);
};

#endif // !CAMERA_H


