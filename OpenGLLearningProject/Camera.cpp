#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>

void Camera::Initialize()
{
	position = { 0.0f, 0.0f, 1.3f };
	direction = { 0.0f, 0.0f, -1.0f };
	up = { 0.0f, 1.0f, 0.0f };

	view = glm::lookAt(position, position + direction, up);

	//projection = glm::perspective(fov, float(800 / 600), farPlane, nearPlane);

	/*
	glm::mat4 test{
		glm::vec4 {0.447f,0,0,0},
		glm::vec4 {0,0.447f,0,0},
		glm::vec4 {0,0,1.004f,-1},
		glm::vec4 {0,0,0.401f,0}
	};
	*/

	float aspect = (float)800 / 600;
	glm::mat4 temp = glm::ortho(-aspect, aspect, -1.0f, 1.0f, nearPlane, farPlane);

	glm::mat4 test{
		glm::vec4 {0.1f,0,0,0},
		glm::vec4 {0,0.1f,0,0},
		glm::vec4 {0,0,0.1f,-1},
		glm::vec4 {0,0,0.1f,0}
	};

	projection = temp;
}
/*
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
*/
void Camera::Draw(const Camera& _camera)
{
}
/*
void Camera::Finalize()
{
}
*/

void Camera::Translate(float _x, float _y, float _z)
{
}
