#include "Transform.h"
#include "GameObject.h"

Transform::Transform(glm::vec3 _position) {
    position = _position;
}

const int Transform::Initialize(GameObject& _gameObject)
{
    return 0;
}

const int Transform::Translate(float _x, float _y, float _z)
{
    modelMatrix = glm::translate(modelMatrix, position);
    return 0;
}

const int Transform::Rotate(float _angle, glm::vec3 _axis)
{
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_angle), _axis);
    return 0;
}

const int Transform::RotateGlobal(float _angle, glm::vec3 _axis)
{
    float distance = glm::length(position);
    float speedConstant = 0.1f;

    if (distance == 0.0f)
        distance = 0.0001f;

    // divide by distance times constant results in planets farther away rotating slower 
    // times distance times constant results in closer planets rotating slower
    float scaledAngle = _angle / (distance * speedConstant);

    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(scaledAngle), _axis) * modelMatrix;
    return 0;
}

const int Transform::Scale(float _x, float _y, float _z)
{
    modelMatrix = glm::scale(modelMatrix, scale);
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

void Transform::Finalize()
{

}

void Transform::InitModelMatrix()
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

glm::mat4 Transform::GetModelMatrix() const
{
    return modelMatrix;
}


