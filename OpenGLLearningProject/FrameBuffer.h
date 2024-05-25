#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GLAD/glad.h>

struct FrameBuffer
{
	FrameBuffer(int _width, int _height);

	void Initialize();
	void CreateRenderBuffer();
	void BindFrameBuffer(GLenum _target);
	void UnbindFrameBuffer(GLenum _target);
	void CreateTexture();
	void Finalize();

	unsigned int  m_depthBuffer{};
	unsigned int m_colBuffers[2];
	int width{}, height{};
	unsigned int m_framebufferID{}, m_renderbufferID{}; //fbo & rbo
	unsigned int m_attributeID{};
	GLenum m_frametarget{}, m_rendertarget{};
};

#endif //!FRAMEBUFFER_H
