#include "BlurFrameBuffer.h"
#include <iostream>

BlurFrameBuffer::BlurFrameBuffer(int _width, int _height)
{
	width = _width;
	height = _height;
}

void BlurFrameBuffer::Initialize()
{
	glGenFramebuffers(2, m_blurFramebufferID);

	CreateTexture();

	/*if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "ERROR: Framebuffer is incomplete!" << std::endl;
	}*/
}

void BlurFrameBuffer::CreateRenderBuffer()
{
}

void BlurFrameBuffer::BindFrameBuffer(GLenum _target, bool _horizontal)
{
	m_frametarget = _target;
	glBindFramebuffer(m_frametarget, m_blurFramebufferID[_horizontal]);
}

void BlurFrameBuffer::UnbindFrameBuffer(GLenum _target)
{
	m_frametarget = _target;
	glBindFramebuffer(m_frametarget, 0);
}

void BlurFrameBuffer::CreateTexture()
{
	glGenTextures(2, m_blurColBuffers);
	for (int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_blurFramebufferID[i]);
		glBindTexture(GL_TEXTURE_2D, m_blurColBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_blurColBuffers[i], 0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BlurFrameBuffer::BindTexture(bool _iteration, bool _horizontal, unsigned int _texID[2])
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _iteration ? _texID[1] : m_blurColBuffers[!_horizontal]);
}

void BlurFrameBuffer::Finalize()
{
}
