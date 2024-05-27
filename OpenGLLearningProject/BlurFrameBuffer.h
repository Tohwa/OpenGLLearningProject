#ifndef BLURFRAMEBUFFER_H
#define BLURFRAMEBUFFER_H

#include <GLAD/glad.h>

struct BlurFrameBuffer
{
	BlurFrameBuffer(int _width, int _height);

	void Initialize();
	void CreateRenderBuffer();
	void BindFrameBuffer(GLenum _target, bool _horizontal);
	void UnbindFrameBuffer(GLenum _target);
	void CreateTexture();
	void BindTexture(bool _iteration, bool _horizontal, unsigned int _texID[2]);
	void Finalize();

	unsigned int m_blurColBuffers[2];
	int width{}, height{};
	unsigned int m_blurFramebufferID[2];
	GLenum m_frametarget{};
};

#endif // !BLURFRAMEBUFFER_H


