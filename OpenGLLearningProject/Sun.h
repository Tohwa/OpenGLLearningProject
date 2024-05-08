#ifndef SUN_H
#define SUN_H

#include "GameObject.h"
#include "Transform.h"
#include "SunMaterial.h"
#include "SunMesh.h"

struct Sun
{
	void Initialize(std::string textures[]) override;

	// Geerbt über GameObject
	void Update();
	void LateUpdate();
	void Draw() override;
	void Finalize() override;
};


#endif // !SUN_H


