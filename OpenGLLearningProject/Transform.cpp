#include "Transform.h"

//Transform::Transform()
//{
//}

Transform::Transform(glm::vec3 _position) {
    position = _position;
}

const int Transform::Initialize(GameObject& _gameObject)
{
    return 0;
}

const int Transform::Update()
{
    return 0;
}

const int Transform::Draw(const Camera& _camera)
{
    return 0;
}

//void Mesh::Translate(float _x, float _y, float _z)
//{
//	position += glm::vec3(_x, _y, _z);
//	model = glm::translate(model, glm::vec3(_x, _y, _z));
//	normal = glm::inverse(glm::mat3(model));
//}
//
//void Mesh::Rotate(float _angle, glm::vec3 _axis)
//{
//	rotation += _axis * _angle;
//	model = glm::rotate(model, glm::radians(_angle), _axis);
//	normal = glm::inverse(glm::mat3(model));
//}
//
//void Mesh::Scale(float _x, float _y, float _z)
//{
//	model = glm::scale(model, glm::vec3(_x, _y, _z));
//}
//
//void Mesh::Orbit(float _radius, glm::vec3 _axis)
//{
//
//	float angleInRadians = glm::radians(angle);
//	float x = _radius * cos(angleInRadians);
//	float z = _radius * sin(angleInRadians);
//
//	model = glm::translate(model, glm::vec3(x, 0.0f, z));
//	model = glm::rotate(model, (angle * 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//}

void Transform::Finalize()
{

}


