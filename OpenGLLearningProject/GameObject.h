#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IEngineObject.h"
#include "Transform.h"

struct GameObject : IEngineObject {

	inline Transform GetTransform() {
		return transform;
	}

	// Geerbt über IEngineObject
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Finalize() override;

private:
	Transform transform;
};

#endif // !GAMEOBJECT_H
