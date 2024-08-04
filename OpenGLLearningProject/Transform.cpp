#include "Transform.h"
#include "GameObject.h"

// Constructor for Transform class, initializes with a position
Transform::Transform(glm::vec3 _position) {
    // Set initial position
    position = _position;
}

/// <summary>
/// Initialize method for Transform class
/// </summary>
/// <param name="_gameObject"> reference to the GameObject this transform belongs to </param>
/// <returns></returns>
const int Transform::Initialize(GameObject& _gameObject)
{
    return 0; // Placeholder for initialization code
}

/// <summary>
/// Translate method for moving the transform
/// </summary>
/// <param name="_x"> translation amount along the respective x-axis </param>
/// <param name="_y"> translation amount along the respective y-axis </param>
/// <param name="_z"> translation amount along the respective z-axis </param>
/// <returns></returns>
const int Transform::Translate(float _x, float _y, float _z)
{
    // Apply translation to the model matrix
    modelMatrix = glm::translate(modelMatrix, position);
    return 0;
}

/// <summary>
/// Rotate method for rotating the transform
/// </summary>
/// <param name="_angle"> angle to rotate </param>
/// <param name="_axis"> axis to rotate around </param>
/// <returns></returns>
const int Transform::Rotate(float _angle, glm::vec3 _axis)
{
    // Apply rotation to the model matrix
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_angle), _axis);
    return 0;
}

/// <summary>
/// RotateGlobal method for rotating the transform around the global origin
/// </summary>
/// <param name="_angle"> angle to rotate </param>
/// <param name="_axis"> axis to rotate around </param>
/// <returns></returns>
const int Transform::RotateGlobal(float _angle, glm::vec3 _axis)
{
    float distance = glm::length(position);
    float speedConstant = 0.1f;

    // Prevent division by zero
    if (distance == 0.0f)
        distance = 0.0001f;

    // Calculate scaled angle for rotation based on distance
    float scaledAngle = _angle / (distance * speedConstant);

    // Apply global rotation to the model matrix
    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(scaledAngle), _axis) * modelMatrix;
    return 0;
}

/// <summary>
/// Scale method for scaling the transform
/// </summary>
/// <param name="_x"> scale factor along the respective x-axis </param>
/// <param name="_y"> scale factor along the respective y-axis </param>
/// <param name="_z"> scale factor along the respective z-axis </param>
/// <returns></returns>
const int Transform::Scale(float _x, float _y, float _z)
{
    // Apply scaling to the model matrix
    modelMatrix = glm::scale(modelMatrix, scale);
    return 0;
}

// Update method for Transform class, placeholder for updates
const int Transform::Update()
{
    return 0; // Placeholder for update code
}

/// <summary>
/// Draw method for Transform class, placeholder for drawing
/// </summary>
/// <param name="_camera"> reference to the camera object </param>
/// <returns></returns>
const int Transform::Draw(const Camera& _camera)
{
    return 0; // Placeholder for draw code
}

// Finalize method for Transform class, placeholder for cleanup
void Transform::Finalize()
{
    // Placeholder for any cleanup operations
}

// InitModelMatrix method for initializing the model matrix
void Transform::InitModelMatrix()
{
    // Set model matrix to identity and apply initial translation
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

/// <summary>
/// GetModelMatrix method for retrieving the model matrix
/// </summary>
/// <returns> returns the current model matrix </returns>
glm::mat4 Transform::GetModelMatrix() const
{
    return modelMatrix;
}