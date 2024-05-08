#ifndef IENGINEOBJECT_H
#define IENGINEOBJECT_H

#include <string>
#include <vector>
#include "IComponent.h"

struct IEngineObject {
	virtual ~IEngineObject() = default;

	virtual void Initialize(std::vector<std::string> _textures, const char* _vertPath, const char* _fragPath) = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;

};

#endif // !IENGINEOBJECT_H
