#ifndef MATERIAL_H
#define MATERIAL_H

#include "IEngineObject.h"

struct Material : IEngineObject {

	// Geerbt über IEngineObject
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Finalize() override;
};

#endif // !MATERIAL_H
