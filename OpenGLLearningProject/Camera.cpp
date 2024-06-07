#include "Camera.h"
#include <GLM/gtc/matrix_transform.hpp>

void Camera::Initialize()
{
	position = { 0.0f, 0.0f, 5.0f };
	direction = { 0.0f, 0.0f, -1.0f };
	up = { 0.0f, 1.0f, 0.0f };

	view = glm::lookAt(position, position + direction, up);

	projection = glm::perspective(fov, (float)1920 / 1080, nearPlane, farPlane);

	
}


void Camera::Update()
{
	//glm::vec3 temp_dir{ direction.x, 0.0f, direction.z };

	if (Input::GetKey(GLFW_KEY_W)) {
		Translate(direction * 10.0f * Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_S)) {
		Translate(-direction * 10.0f * Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_A)) {
		Translate(-glm::normalize(glm::cross(direction, up)) * 10.0f * Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_D)) {
		Translate(glm::normalize(glm::cross(direction, up)) * 10.0f * Time::GetDeltaTime());
	}
	
	glm::vec2 newMousePos = Input::GetMousePos();

	if (m_firstMouse) {

		m_lastMousePos = newMousePos;
		m_firstMouse = false;		
	}

	float xoffset{ newMousePos.x - m_lastMousePos.x };
	float yoffset{ m_lastMousePos.y - newMousePos.y };


	m_lastMousePos = newMousePos;

	float sens{ 10.0f * Time::GetDeltaTime() };

	xoffset *= sens;
	yoffset *= sens;

	yaw += xoffset;
	pitch += yoffset;


	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	glm::vec3 dir{};

	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	direction = glm::normalize(dir);



	view = glm::lookAt(position, position + direction, up);
}

/*
void Camera::LateUpdate()
{
}

void Camera::Draw()
{
}

void Camera::Draw(const Camera& _camera)
{
}

void Camera::Finalize()
{
}
*/

void Camera::Translate(glm::vec3 _dir)
{
	position += _dir;
}
