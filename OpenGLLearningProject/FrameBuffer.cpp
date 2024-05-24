#include "FrameBuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer(int _width, int _height)
{
	width = _width;
	height = _height;
}

void FrameBuffer::Initialize()
{
	glGenFramebuffers(1, &m_framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);


	CreateTexture();
	CreateRenderBuffer();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "ERROR: Framebuffer is incomplete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::CreateRenderBuffer()
{
	glGenRenderbuffers(1, &m_renderbufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferID);
}

void FrameBuffer::BindFrameBuffer(GLenum _target)
{
	m_frametarget = _target;
	glBindFramebuffer(m_frametarget, m_framebufferID);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::UnbindFrameBuffer(GLenum _target)
{
	m_frametarget = _target;
	glBindFramebuffer(m_frametarget, 0);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void FrameBuffer::CreateTexture()
{

	glGenTextures(2, m_colBuffers);
	for (int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_colBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colBuffers[i], 0);
	}

	glGenTextures(1, &m_depthBuffer);
	glBindTexture(GL_TEXTURE_2D, m_depthBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthBuffer, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBuffer::Finalize()
{
	glDeleteBuffers(1, &m_framebufferID);
	glDeleteBuffers(1, &m_renderbufferID);
	glDeleteTextures(1, &m_depthBuffer);
}
