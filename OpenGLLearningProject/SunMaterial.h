#ifndef SUNMATERIAL_H
#define SUNMATERIAL_H

#include "IMaterial.h"

struct SunMaterial : IMaterial
{
	const int Initialize(GameObject& _gameObject) override;
	void InitShader();
	const int Update() override;
	const int Draw() override;
	void Finalize() override;
};

#endif // !SUNMATERIAL_H


