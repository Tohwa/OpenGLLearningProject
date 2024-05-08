#ifndef CAMERA_H
#define CAMERA_H

#include <GLM/glm.hpp>

#include "Input.h"
#include "Time.h"

struct Camera //: IComponent
{
	glm::vec3 position{};
	glm::vec3 direction{};
	glm::vec3 up{};

	glm::mat4 view{};
	glm::mat4 projection{};

	float nearPlane{ 0.1f }, farPlane{ 100.0f };
	float fov{ glm::radians(45.0f)};

	// Geerbt über IEngineObject
	void Initialize();
	/*
	void Initialize(SShader*) override;
	*/
	void Update();
	/*
	void LateUpdate() override;
	void Draw() override;
	
	void Draw(const Camera&);
	
	void Finalize() override;
	*/
	void Translate(glm::vec3 _dir);

private:
	bool m_firstMouse{ true };
	glm::vec2 m_lastMousePos{};
	float yaw{ -90.0f };
	float pitch{};
};

#endif // !CAMERA_H


