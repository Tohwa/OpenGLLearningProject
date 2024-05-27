#ifndef QUADVIEW_H
#define QUADVIEW_H

#include "Buffer.h"
#include "Shader.h"
#include <vector>

struct QuadView
{
	void CreateQuadBuffer(SShader &_shader);
	void RenderQuad();

private:
	unsigned int frameVAO{};
	SBuffer frameBuffer{};
	SShader m_shader{};
};

#endif // !QUADVIEW_H


