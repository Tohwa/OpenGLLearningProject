#ifndef IENGINEOBJECT_H
#define IENGINEOBJECT_H

#include "Shader.h"
#include "Camera.h"
#include <string>

struct IEngineObject {
	virtual ~IEngineObject() = default;

	virtual void Initialize(std::string textures[]) = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;

};

#endif // !IENGINEOBJECT_H
