#ifndef MESH_H
#define MESH_H

#include "IEngineObject.h"

struct Mesh : IEngineObject {

	// Geerbt über IEngineObject
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Finalize() override;
};
#endif // !MESH_H
