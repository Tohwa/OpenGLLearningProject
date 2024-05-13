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
    /*position += glm::vec3(_x, _y, _z);
    model = glm::translate(model, glm::vec3(_x, _y, _z));
    normal = glm::inverse(glm::mat3(model));*/

    return 0;
}

const int Transform::Rotate(float _angle, glm::vec3 _axis)
{
    /*rotation += _axis * _angle;
    model = glm::rotate(model, glm::radians(_angle), _axis);
    normal = glm::inverse(glm::mat3(model));*/
    return 0;
}

const int Transform::Scale(float _x, float _y, float _z)
{
    /*model = glm::scale(model, glm::vec3(_x, _y, _z));*/
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


