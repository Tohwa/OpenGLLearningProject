#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <GLM/glm.hpp>
#include <GLM/vec3.hpp>
//#include <GLFW/glfw3.h>
#include <GLM/gtx/transform.hpp>
#include <string>
#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Vertex.h"
#include "ObjLoader.h"
#include "Buffer.h"



struct GameObject;

struct IComponent
{
	virtual const int Initialize(GameObject& _gameObject) = 0;
	virtual const int Update() = 0;
	virtual const int Draw(const Camera& _camera) = 0;
	virtual void Finalize() = 0;
};

#endif // !ICOMPONENT_H




