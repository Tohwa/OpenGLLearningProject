#ifndef MESH_H
#define MESH_H

#include "IEngineObject.h"

struct Mesh : IEngineObject {

	// Geerbt �ber IEngineObject
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Finalize() override;
};
#endif // !MESH_H
