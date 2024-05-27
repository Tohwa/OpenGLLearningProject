#include "QuadView.h"



void QuadView::CreateQuadBuffer(SShader &_shader)
{
	float quad[] = {
		-1.0f,1.0f,0.0f,1.0f,
		-1.0f,-1.0f,0.0f,0.0f,
		1.0f,-1.0f,1.0f,0.0f,
		-1.0f,1.0f,0.0f,1.0f,
		1.0f,-1.0f,1.0f,0.0f,
		1.0f,1.0f,1.0f,1.0f
	};

	m_shader = _shader;

	glGenVertexArrays(1, &frameVAO);
	glBindVertexArray(frameVAO);

	frameBuffer.CreateBufferObject();
	frameBuffer.Bind(GL_ARRAY_BUFFER);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, &quad, GL_STATIC_DRAW); // <- HIER WAR DER FEHLER! frameVAO genutzt...

	const char* attributeName = "aPos";
	unsigned int attributeID = m_shader.GetAttributeLocation(attributeName);
	frameBuffer.SetAttributeID(attributeName, attributeID);
	frameBuffer.LinkAttribute(2, GL_FLOAT, false, sizeof(float) * 4, 0);

	attributeName = "aUVs";
	attributeID = m_shader.GetAttributeLocation(attributeName);
	frameBuffer.SetAttributeID(attributeName, attributeID);
	frameBuffer.LinkAttribute(2, GL_FLOAT, false, (sizeof(float) * 4), (void*)(sizeof(float) * 2));

	glBindVertexArray(0);
}

void QuadView::RenderQuad()
{
	glBindVertexArray(frameVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
