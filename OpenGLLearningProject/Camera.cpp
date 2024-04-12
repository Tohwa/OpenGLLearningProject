#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>

void Camera::Initialize()
{
	position = { 0.0f, 0.0f, 2.0f };
	direction = { 0.0f, 0.0f, -1.0f };
	up = { 0.0f, 1.0f, 0.0f };

	view = glm::lookAt(position, position + direction, up);

	projection = glm::perspective(fov, float(800/600), farPlane, nearPlane);
}

void Camera::Initialize(SShader* _shader)
{
}

void Camera::Update()
{

}

void Camera::LateUpdate()
{
}

void Camera::Draw()
{
}

void Camera::Draw(const Camera&)
{
}

void Camera::Finalize()
{
}

void Camera::Translate(float, float, float)
{
}
