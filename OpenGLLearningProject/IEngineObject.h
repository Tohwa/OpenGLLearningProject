#ifndef IENGINEOBJECT_H
#define IENGINEOBJECT_H

#include "Shader.h"
#include "Camera.h"

struct IEngineObject {
	virtual ~IEngineObject() = default;

	virtual void Initialize() = 0;
	virtual void Initialize(SShader*) = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Draw(const Camera&) = 0;
	virtual void Finalize() = 0;
};

#endif // !IENGINEOBJECT_H
